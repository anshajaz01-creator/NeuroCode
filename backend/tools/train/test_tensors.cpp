#include <cstdio>
#include <map>
#include <set>

#include "ml/Dataset.hpp"

int main() {
    nc::Dataset ds("data/dataset.jsonl", "src/ml/labels.json");
    const auto& s = ds.standardizer();

    // 1. tensor shapes and types
    for (const char* split : {"train", "val", "test"}) {
        auto t = ds.tensors(ds.indicesOf(split), s);
        std::printf("%-5s x %s  y %s\n", split,
                    c10::str(t.x.sizes()).c_str(), c10::str(t.y.sizes()).c_str());
    }

    // 2. the tensor really holds the standardized values of the right row
    auto idx = ds.indicesOf("train");
    auto tr = ds.tensors(idx, s);
    auto z = s.apply(ds.rows()[idx[0]].features);
    std::printf("\nfirst train row, first 3 features\n  apply():  %.4f %.4f %.4f\n",
                z[0], z[1], z[2]);
    std::printf("  tensor:   %.4f %.4f %.4f\n", tr.x[0][0].item<float>(),
                tr.x[0][1].item<float>(), tr.x[0][2].item<float>());
    std::printf("  label: tensor %lld, row %lld\n", (long long)tr.y[0].item<int64_t>(),
                (long long)ds.rows()[idx[0]].label);

    // 3. grouped folds
    auto folds = ds.groupFolds(5, 42);
    std::vector<int> rows_per_fold(5, 0);
    std::map<std::string, std::set<int>> folds_of_group;
    for (size_t i = 0; i < folds.size(); ++i) {
        rows_per_fold[folds[i]]++;
        folds_of_group[ds.rows()[i].group].insert(folds[i]);
    }
    std::printf("\n5 folds, rows per fold:");
    for (int n : rows_per_fold) std::printf(" %d", n);
    int split_groups = 0;
    for (const auto& [g, fs] : folds_of_group) if (fs.size() > 1) ++split_groups;
    std::printf("\ngroups: %zu, groups appearing in more than one fold: %d\n",
                folds_of_group.size(), split_groups);
}