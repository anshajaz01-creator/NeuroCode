#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <torch/torch.h>

namespace nc {

// One line of dataset.jsonl, held in memory. Features stay RAW here.
struct Row {
    std::vector<float> features;  // 53 numbers (features)
    int64_t label = 0;            // converts index into labels.json, 0..11
    std::string group;            // seed or contest problem
    std::string split;            // "train" , "val" , "test"
};
// Rescales features to z-scores: z = (x - mean) / stdev.
struct Standardizer {
    std::vector<float> mean, stdev;

    // Compute mean/stdev over the rows listed in idx (callers pass TRAIN rows only).
    static Standardizer fit(const std::vector<Row>& rows, const std::vector<size_t>& idx,
                            int n_features);

    // Rescale one raw feature vector.
    std::vector<float> apply(const std::vector<float>& raw) const;
};
// A set of samples as tensors, ready for the network.
struct SplitTensors {
    torch::Tensor x;  // [n, n_features] float32, standardized
    torch::Tensor y;  // [n] int64 class indices
    int64_t size() const { return y.defined() ? y.size(0) : 0; }
};
std::vector<std::string> loadLabels(const std::string& labels_path);

class Dataset {
public:
    Dataset(const std::string& jsonl_path, const std::string& labels_path);

    std::vector<size_t> indicesOf(const std::string& split) const;
    const Standardizer& standardizer() const { return std_; }
    // Standardize the listed rows with s and pack them as tensors.
    SplitTensors tensors(const std::vector<size_t>& idx, const Standardizer& s) const;
    // Grouped k-fold: every group goes to exactly one fold. Returns the fold of each row.
    std::vector<int> groupFolds(int k, uint64_t seed) const;
    const std::vector<Row>&  rows() const { return rows_; }   
    //const std::vector<Row>& returns a reference: the caller reads the original rows without
    //  copying 2000 of them.The underscore in rows_ is just a convention meaning “member variable”.
    const std::vector<std::string>& labels() const { return labels_; }
    int numFeatures() const { return n_features_; }
    int numClasses() const { return static_cast<int>(labels_.size()); }

private:
    std::vector<std::string> labels_;
    std::vector<Row> rows_;
    int n_features_ = 0;
    Standardizer std_;
};

}  // namespace nc