#include "ml/Dataset.hpp"

#include <fstream>
#include <map>
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include <random>
#include <set>
#include <nlohmann/json.hpp>

namespace nc {

using json = nlohmann::json;

std::vector<std::string> loadLabels(const std::string& labels_path) {
    std::ifstream in(labels_path);
    if (!in) throw std::runtime_error("cannot open " + labels_path);
    return json::parse(in).at("labels").get<std::vector<std::string>>();
}
Standardizer Standardizer::fit(const std::vector<Row>& rows, const std::vector<size_t>& idx,
                               int n_features) {
    Standardizer s;
    s.mean.assign(n_features, 0.f);
    s.stdev.assign(n_features, 0.f);
    if (idx.empty()) {                     // nothing to fit on: identity transform
        s.stdev.assign(n_features, 1.f);
        return s;
    }

    // mean: sum each column, divide by row count
    for (size_t i : idx)
        for (int f = 0; f < n_features; ++f) s.mean[f] += rows[i].features[f];
    for (auto& m : s.mean) m /= static_cast<float>(idx.size());

    // standard deviation: sqrt of the average squared distance from the mean
    for (size_t i : idx)
        for (int f = 0; f < n_features; ++f) {
            float d = rows[i].features[f] - s.mean[f];
            s.stdev[f] += d * d;
        }
    for (auto& v : s.stdev) {
        v = std::sqrt(v / static_cast<float>(idx.size()));
        if (v < 1e-8f) v = 1.f;            // constant feature: avoid dividing by zero
    }
    return s;
}

std::vector<float> Standardizer::apply(const std::vector<float>& raw) const {
    std::vector<float> z(raw.size());
    for (size_t f = 0; f < raw.size(); ++f) z[f] = (raw[f] - mean[f]) / stdev[f];
    return z;
}

std::vector<size_t> Dataset::indicesOf(const std::string& split) const {
    std::vector<size_t> idx;
    for (size_t i = 0; i < rows_.size(); ++i)
        if (rows_[i].split == split) idx.push_back(i);
    return idx;
}

SplitTensors Dataset::tensors(const std::vector<size_t>& idx, const Standardizer& s) const {
    SplitTensors t;
    if (idx.empty()) return t;

    // lay everything out in one long list: row 0's 53 values, then row 1's, ...
    std::vector<float> flat;
    std::vector<int64_t> ys;
    flat.reserve(idx.size() * n_features_);
    for (size_t i : idx) {
        auto z = s.apply(rows_[i].features);
        flat.insert(flat.end(), z.begin(), z.end());
        ys.push_back(rows_[i].label);
    }

    auto n = static_cast<int64_t>(idx.size());
    // from_blob views our memory as an n x 53 grid; clone() gives the tensor its own copy,
    // because flat and ys are destroyed when this function returns
    t.x = torch::from_blob(flat.data(), {n, n_features_}, torch::kFloat32).clone();
    t.y = torch::from_blob(ys.data(), {n}, torch::kInt64).clone();
    return t;
}

std::vector<int> Dataset::groupFolds(int k, uint64_t seed) const {
    // every distinct group, in a fixed order
    std::set<std::string> unique;
    for (const auto& r : rows_) unique.insert(r.group);
    std::vector<std::string> groups(unique.begin(), unique.end());

    // shuffle GROUPS (not rows), then deal them into k piles like cards
    std::mt19937_64 rng(seed);
    std::shuffle(groups.begin(), groups.end(), rng);
    std::map<std::string, int> fold_of;
    for (size_t i = 0; i < groups.size(); ++i) fold_of[groups[i]] = static_cast<int>(i % k);

    // each row inherits its group's fold
    std::vector<int> out;
    out.reserve(rows_.size());
    for (const auto& r : rows_) out.push_back(fold_of[r.group]);
    return out;
}

Dataset::Dataset(const std::string& jsonl_path, const std::string& labels_path) {
    labels_ = loadLabels(labels_path);

    // label name -> number, e.g. "binary_search" -> 0
    std::map<std::string, int64_t> index;
    for (size_t i = 0; i < labels_.size(); ++i) index[labels_[i]] = static_cast<int64_t>(i);

    std::ifstream in(jsonl_path);
    if (!in) throw std::runtime_error("cannot open " + jsonl_path);

    std::string line;
    int line_no = 0;
    while (std::getline(in, line)) {
        ++line_no;
        if (line.empty()) continue;
        json r = json::parse(line);

        Row row;
        auto label = r.at("label").get<std::string>();
        auto it = index.find(label);
        if (it == index.end())
            throw std::runtime_error("line " + std::to_string(line_no) + ": label '" + label +
                                     "' is not in labels.json");
        row.label = it->second;
        row.features = r.at("features").get<std::vector<float>>();
        row.group = r.at("group_id").get<std::string>();
        row.split = r.at("split").get<std::string>();

        if (n_features_ == 0) n_features_ = static_cast<int>(row.features.size());
        if (static_cast<int>(row.features.size()) != n_features_)
            throw std::runtime_error("line " + std::to_string(line_no) + ": feature length mismatch");

        rows_.push_back(std::move(row));
    }
    if (rows_.empty()) throw std::runtime_error("no samples in " + jsonl_path);
        std_ = Standardizer::fit(rows_, indicesOf("train"), n_features_);
}

}  // namespace nc

//r.at("label") throws if the key is missing; r["label"] would silently create it. .at() is the safe choice for reading.
//index.find(label) returns index.end() when not found. That’s how C++ maps say “no such key”.
//std::move(row) hands the row’s memory to the vector instead of copying it. Fine here because we don’t use row again.