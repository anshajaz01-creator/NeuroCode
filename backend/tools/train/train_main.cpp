// NeuroCode model trainer. Run from backend/:
//   ./tools/train/build/nc_train            final model only
//   ./tools/train/build/nc_train --cv 5     cross-validate first, then final model
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <string>

#include "ml/Dataset.hpp"
#include "ml/Metrics.hpp"
#include "ml/Model.hpp"
#include "ml/Predictor.hpp"
#include "ml/Trainer.hpp"

int main(int argc, char** argv) {
    // ---- 1. options ----
    int cv_folds = 0;
    std::string version;
    nc::TrainConfig cfg;
    for (int i = 1; i < argc; ++i) {
        std::string a = argv[i];
        auto next = [&] { return std::string(i + 1 < argc ? argv[++i] : ""); };
        if (a == "--cv") cv_folds = std::stoi(next());
        else if (a == "--version") version = next();
        else if (a == "--patience") cfg.patience = std::stoi(next());
        else if (a == "--lr") cfg.lr = std::stod(next());
        else if (a == "--seed") cfg.seed = std::stoull(next());
        else { std::printf("usage: nc_train [--cv K] [--version NAME] [--patience N] [--lr X] [--seed N]\n"); return 2; }
    }
    if (version.empty()) {  // default name: v + date + time, so newer names sort later
        char buf[32];
        std::time_t t = std::time(nullptr);
        std::strftime(buf, sizeof buf, "v%Y%m%d-%H%M", std::localtime(&t));
        version = buf;
    }

    // ---- 2. data ----
    nc::Dataset ds("data/dataset.jsonl", "src/ml/labels.json");
    const int C = ds.numClasses();
    auto tr = ds.tensors(ds.indicesOf("train"), ds.standardizer());
    auto va = ds.tensors(ds.indicesOf("val"), ds.standardizer());
    auto te = ds.tensors(ds.indicesOf("test"), ds.standardizer());
    std::printf("dataset: %zu samples, %d features, %d classes (train %lld, val %lld, test %lld)\n",
                ds.rows().size(), ds.numFeatures(), C, (long long)tr.size(),
                (long long)va.size(), (long long)te.size());

    // ---- 3. cross-validation (optional) ----
    double cv_acc = -1;
    if (cv_folds > 1) {
        std::printf("\n== grouped %d-fold cross-validation ==\n", cv_folds);
        auto cv = nc::crossValidate(ds, cv_folds, cfg);
        for (size_t f = 0; f < cv.fold_accuracy.size(); ++f)
            std::printf("  fold %zu: %5.1f%%  (best epoch %d)\n", f + 1,
                        100 * cv.fold_accuracy[f], cv.fold_best_epoch[f]);
        cv_acc = cv.accuracy;
        std::printf("  CV accuracy: %.1f%%\n", 100 * cv_acc);
        nc::printPerClass(cv.pooled, ds.labels());
    }

    // ---- 4. final model ----
    std::printf("\n== final model ==\n");
    nc::MLP model(ds.numFeatures(), C);
    auto res = nc::train(model, tr, va, C, cfg, [](const nc::EpochStats& s) {
        if (s.epoch == 1 || s.epoch % 10 == 0)
            std::printf("  epoch %3d  train %.4f  val %.4f  val acc %5.1f%%\n",
                        s.epoch, s.train_loss, s.val_loss, 100 * s.val_accuracy);
    });
    std::printf("  stopped at epoch %d, best epoch %d\n", res.epochs_run, res.best_epoch);

    auto ev_va = nc::evaluate(model, va.x, va.y, C);
    auto ev_te = nc::evaluate(model, te.x, te.y, C);
    std::printf("\n  val acc %.1f%%   test acc %.1f%%\n\n", 100 * ev_va.accuracy, 100 * ev_te.accuracy);
    nc::printPerClass(ev_te, ds.labels());
    std::printf("\n  test confusion (rows = true, columns = predicted):\n");
    nc::printConfusion(ev_te, ds.labels());

    // ---- 5. save ----
    std::filesystem::create_directories("models");
    std::string base = "models/" + version;
    nc::ModelInfo info;
    info.version = version;
    info.n_features = ds.numFeatures();
    info.labels = ds.labels();
    info.mean = ds.standardizer().mean;
    info.stdev = ds.standardizer().stdev;
    info.val_accuracy = ev_va.accuracy;
    info.test_accuracy = ev_te.accuracy;
    info.cv_accuracy = cv_acc;
    info.best_epoch = res.best_epoch;
    info.dataset_size = static_cast<int>(ds.rows().size());
    nc::saveCheckpoint(model, info, base);
    std::printf("\nsaved %s.pt + %s.json\n", base.c_str(), base.c_str());

    // ---- 6. reload check: saved model must reproduce the in-memory one ----
    nc::Predictor p;
    if (!p.loadModel(base + ".pt")) { std::printf("reload FAILED\n"); return 1; }
    torch::NoGradGuard ng;
    model->eval();
    auto mem_pred = model->forward(te.x).argmax(1);
    auto test_idx = ds.indicesOf("test");
    int same = 0;
    for (size_t t = 0; t < test_idx.size(); ++t) {
        auto g = p.predict(ds.rows()[test_idx[t]].features, 1);
        if (g[0].label == ds.labels()[mem_pred[t].item<int64_t>()]) ++same;
    }
    std::printf("reload check: %d/%zu identical  %s\n", same, test_idx.size(),
                same == (int)test_idx.size() ? "OK" : "MISMATCH");
    return same == (int)test_idx.size() ? 0 : 1;
}