#include <cmath>
#include <cstdio>

#include "ml/Dataset.hpp"
#include "ml/Metrics.hpp"
#include "ml/Model.hpp"

int main() {
    torch::manual_seed(42);
    nc::Dataset ds("data/dataset.jsonl", "src/ml/labels.json");
    nc::MLP model(ds.numFeatures(), ds.numClasses());

    auto val = ds.tensors(ds.indicesOf("val"), ds.standardizer());
    auto r = nc::evaluate(model, val.x, val.y, ds.numClasses());

    std::printf("UNTRAINED model on val (%lld samples)\n", (long long)val.size());
    std::printf("  loss %.3f   (pure guessing = ln 12 = %.3f)\n", r.loss, std::log(12.0));
    std::printf("  accuracy %.1f%%   (pure guessing = %.1f%%)\n\n", 100 * r.accuracy, 100.0 / 12);
    nc::printPerClass(r, ds.labels());
    std::printf("\nconfusion matrix (rows = true, columns = predicted):\n");
    nc::printConfusion(r, ds.labels());
}