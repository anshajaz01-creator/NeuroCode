#pragma once
#include <functional>

#include "ml/Dataset.hpp"
#include "ml/Model.hpp"

namespace nc {

struct TrainConfig {
    int max_epochs = 300;
    int batch_size = 32;
    double lr = 1e-3;            // learning rate
    double weight_decay = 1e-4;  // small penalty on large weights, fights overfitting
    int patience = 25;          // stop after this many epochs without val-loss improvement
    bool class_weights = true;  // weight the loss by inverse class frequency
    uint64_t seed = 42;
};

struct EpochStats {
    int epoch = 0;
    double train_loss = 0, val_loss = 0, val_accuracy = 0;
};

struct TrainResult {
    int epochs_run = 0;
    int best_epoch = 0;
    double best_val_loss = 0;
};

// Called once per epoch: the command-line tool prints it, the backend can send it
// over the WebSocket to the live training chart.
using EpochCallback = std::function<void(const EpochStats&)>;

TrainResult train(MLP& model, const SplitTensors& train_set, const SplitTensors& val_set,
                  int n_classes, const TrainConfig& cfg, const EpochCallback& on_epoch = nullptr);


// Everything the predictor needs besides the weights.
struct ModelInfo {
    std::string version;
    int n_features = 0;
    std::vector<std::string> labels;
    std::vector<float> mean, stdev;   // standardization stats from TRAINING data
    double val_accuracy = 0, test_accuracy = 0, cv_accuracy = -1;  // -1 = not measured
    int best_epoch = 0;
    int dataset_size = 0;
};

// Writes <path>.pt (weights) and <path>.json (ModelInfo). They always travel together.
void saveCheckpoint(MLP& model, const ModelInfo& info, const std::string& path_no_ext);
                  
}  // namespace nc