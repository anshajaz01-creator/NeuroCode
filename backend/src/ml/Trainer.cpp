#include "ml/Trainer.hpp"

#include <ctime>
#include <fstream>
#include <limits>

#include <nlohmann/json.hpp>

#include "ml/Metrics.hpp"

namespace nc {

TrainResult train(MLP& model, const SplitTensors& train_set, const SplitTensors& val_set,
                  int n_classes, const TrainConfig& cfg, const EpochCallback& on_epoch) {
    torch::manual_seed(cfg.seed);
    TrainResult res;

    // class weights = total / (n_classes * count per class)
    torch::Tensor weights;
    if (cfg.class_weights) {
        auto counts = torch::bincount(train_set.y, {}, n_classes).to(torch::kFloat32);
        weights = counts.sum() / (n_classes * counts.clamp_min(1.0));
    }
    auto loss_opts = torch::nn::functional::CrossEntropyFuncOptions();
    if (weights.defined()) loss_opts = loss_opts.weight(weights);

    torch::optim::Adam optim(model->parameters(),
                             torch::optim::AdamOptions(cfg.lr).weight_decay(cfg.weight_decay));

    // early stopping state
    double best = std::numeric_limits<double>::infinity();
    int since_best = 0;
    std::vector<torch::Tensor> best_state;
    auto snapshot = [&] {
        torch::NoGradGuard g;
        best_state.clear();
        for (auto& p : model->parameters()) best_state.push_back(p.detach().clone());
    };

    const int64_t n = train_set.size();
    for (int epoch = 1; epoch <= cfg.max_epochs; ++epoch) {
        model->train();
        auto perm = torch::randperm(n, torch::kInt64);
        double loss_sum = 0;

        for (int64_t start = 0; start < n; start += cfg.batch_size) {
            auto idx = perm.slice(0, start, std::min(n, start + cfg.batch_size));
            auto xb = train_set.x.index_select(0, idx);
            auto yb = train_set.y.index_select(0, idx);

            optim.zero_grad();
            auto loss = torch::nn::functional::cross_entropy(model->forward(xb), yb, loss_opts);
            loss.backward();
            optim.step();
            loss_sum += loss.item<double>() * idx.size(0);
        }

        EpochStats st;
        st.epoch = epoch;
        st.train_loss = loss_sum / static_cast<double>(n);
        auto ev = evaluate(model, val_set.x, val_set.y, n_classes);
        st.val_loss = ev.loss;
        st.val_accuracy = ev.accuracy;
        res.epochs_run = epoch;
        if (on_epoch) on_epoch(st);

        // keep the best, stop when no improvement for `patience` epochs
        if (st.val_loss < best - 1e-5) {
            best = st.val_loss;
            res.best_epoch = epoch;
            since_best = 0;
            snapshot();
        } else if (++since_best >= cfg.patience) {
            break;
        }
    }

    // put the best epoch's weights back into the model
    if (!best_state.empty()) {
        torch::NoGradGuard g;
        auto params = model->parameters();
        for (size_t i = 0; i < params.size(); ++i) params[i].copy_(best_state[i]);
    }
    res.best_val_loss = best;
    return res;
}

void saveCheckpoint(MLP& model, const ModelInfo& info, const std::string& path_no_ext) {
    torch::save(model, path_no_ext + ".pt");   // weights, by registered layer name

    std::time_t now = std::time(nullptr);
    char stamp[32];
    std::strftime(stamp, sizeof stamp, "%Y-%m-%dT%H:%M:%S", std::localtime(&now));

    nlohmann::json j;
    j["version"] = info.version;
    j["feature_version"] = 2;                  // features.py v2
    j["n_features"] = info.n_features;
    j["labels"] = info.labels;
    j["feature_mean"] = info.mean;
    j["feature_std"] = info.stdev;
    j["architecture"] = {{"hidden", {128, 64}}, {"dropout", {0.3, 0.2}}};
    j["metrics"] = {{"val_accuracy", info.val_accuracy},
                    {"test_accuracy", info.test_accuracy},
                    {"cv_accuracy", info.cv_accuracy}};
    j["best_epoch"] = info.best_epoch;
    j["dataset_size"] = info.dataset_size;
    j["trained_at"] = stamp;

    std::ofstream(path_no_ext + ".json") << j.dump(2) << "\n";
}

CVResult crossValidate(const Dataset& ds, int k, const TrainConfig& cfg) {
    const int C = ds.numClasses();
    auto folds = ds.groupFolds(k, cfg.seed);

    CVResult out;
    out.pooled.confusion.assign(C, std::vector<int64_t>(C, 0));

    for (int f = 0; f < k; ++f) {
        // split rows by fold: test = f, val = next fold, train = the rest
        std::vector<size_t> tr, va, te;
        for (size_t i = 0; i < ds.rows().size(); ++i) {
            if (folds[i] == f) te.push_back(i);
            else if (folds[i] == (f + 1) % k) va.push_back(i);
            else tr.push_back(i);
        }

        // standardize with THIS round's training rows only
        auto st = Standardizer::fit(ds.rows(), tr, ds.numFeatures());
        auto T = ds.tensors(tr, st), V = ds.tensors(va, st), E = ds.tensors(te, st);

        MLP model(ds.numFeatures(), C);  // fresh, untrained model every round
        auto res = train(model, T, V, C, cfg);
        auto ev = evaluate(model, E.x, E.y, C);

        for (int t = 0; t < C; ++t)
            for (int p = 0; p < C; ++p) out.pooled.confusion[t][p] += ev.confusion[t][p];
        out.fold_accuracy.push_back(ev.accuracy);
        out.fold_best_epoch.push_back(res.best_epoch);
    }

    // pooled accuracy and per-class accuracy from the summed confusion matrix
    int64_t correct = 0, total = 0;
    out.pooled.per_class_accuracy.assign(C, -1.0);
    out.pooled.per_class_count.assign(C, 0);
    for (int c = 0; c < C; ++c) {
        int64_t n = 0;
        for (int p = 0; p < C; ++p) n += out.pooled.confusion[c][p];
        out.pooled.per_class_count[c] = n;
        if (n) out.pooled.per_class_accuracy[c] = double(out.pooled.confusion[c][c]) / n;
        correct += out.pooled.confusion[c][c];
        total += n;
    }
    out.accuracy = total ? double(correct) / total : 0.0;
    out.pooled.accuracy = out.accuracy;
    return out;
}

}  // namespace nc
