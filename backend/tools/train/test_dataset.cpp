#include <cstdio>
#include <map>

#include "ml/Dataset.hpp"

int main() {
    nc::Dataset ds("data/dataset.jsonl", "src/ml/labels.json");

    std::printf("samples: %zu, features: %d, classes: %d\n",
                ds.rows().size(), ds.numFeatures(), ds.numClasses());

    std::map<std::string, int> per_split;
    std::vector<int> per_label(ds.numClasses(), 0);
    for (const auto& r : ds.rows()) {
        per_split[r.split]++;
        per_label[r.label]++;
    }
    for (const auto& [split, n] : per_split) std::printf("  %-6s %d\n", split.c_str(), n);
    for (int c = 0; c < ds.numClasses(); ++c)
        std::printf("  %-26s %d\n", ds.labels()[c].c_str(), per_label[c]);

    const auto& first = ds.rows()[0];
    std::printf("first row: label %lld (%s), group %s, split %s, feature[0] = %.1f\n",
                (long long)first.label, ds.labels()[first.label].c_str(),
                first.group.c_str(), first.split.c_str(), first.features[0]);
}