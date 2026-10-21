#include <cmath>
#include <cstdio>

#include "ml/Dataset.hpp"

// mean and stdev of feature f over the given rows, after standardizing
static void stats(const nc::Dataset& ds, const std::vector<size_t>& idx, int f,
                  double& mean, double& sd) {
    mean = 0; sd = 0;
    for (size_t i : idx) mean += ds.standardizer().apply(ds.rows()[i].features)[f];
    mean /= idx.size();
    for (size_t i : idx) {
        double d = ds.standardizer().apply(ds.rows()[i].features)[f] - mean;
        sd += d * d;
    }
    sd = std::sqrt(sd / idx.size());
}

int main() {
    nc::Dataset ds("data/dataset.jsonl", "src/ml/labels.json");
    const auto& s = ds.standardizer();

    std::printf("fitted on train only (%zu rows)\n", ds.indicesOf("train").size());
    std::printf("  feature  raw mean  raw stdev\n");
    for (int f : {0, 4, 20, 39, 17})
        std::printf("  %7d  %8.3f  %9.3f\n", f, s.mean[f], s.stdev[f]);

    std::printf("\nafter standardizing, feature 0 (loop_count):\n");
    for (const char* split : {"train", "val", "test"}) {
        double m, sd;
        stats(ds, ds.indicesOf(split), 0, m, sd);
        std::printf("  %-5s  mean %7.3f   stdev %6.3f\n", split, m, sd);
    }
}