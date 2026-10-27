#include <cstdio>
#include <filesystem>

#include "ml/Dataset.hpp"
#include "ml/Metrics.hpp"
#include "ml/Model.hpp"
#include "ml/Trainer.hpp"

int main() {
    nc::Dataset ds("data/dataset.jsonl", "src/ml/labels.json");
    auto tr = ds.tensors(ds.indicesOf("train"), ds.standardizer());
    auto va = ds.tensors(ds.indicesOf("val"), ds.standardizer());
    auto te = ds.tensors(ds.indicesOf("test"), ds.standardizer());

    nc::MLP model(ds.numFeatures(), ds.numClasses());
    auto res = nc::train(model, tr, va, ds.numClasses(), nc::TrainConfig{});

    nc::ModelInfo info;
    info.version = "test-save";
    info.n_features = ds.numFeatures();
    info.labels = ds.labels();
    info.mean = ds.standardizer().mean;
    info.stdev = ds.standardizer().stdev;
    info.val_accuracy = nc::evaluate(model, va.x, va.y, ds.numClasses()).accuracy;
    info.test_accuracy = nc::evaluate(model, te.x, te.y, ds.numClasses()).accuracy;
    info.best_epoch = res.best_epoch;
    info.dataset_size = static_cast<int>(ds.rows().size());

    std::filesystem::create_directories("models");
    nc::saveCheckpoint(model, info, "models/test-save");

    for (const char* f : {"models/test-save.pt", "models/test-save.json"})
        std::printf("%-24s %8lld bytes\n", f, (long long)std::filesystem::file_size(f));
    std::printf("val acc %.1f%%, test acc %.1f%%, best epoch %d\n",
                100 * info.val_accuracy, 100 * info.test_accuracy, info.best_epoch);
}