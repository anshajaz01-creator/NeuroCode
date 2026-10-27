#include <cstdio>

#include "ml/Dataset.hpp"
#include "ml/Metrics.hpp"
#include "ml/Model.hpp"
#include "ml/Trainer.hpp"

int main() {
    nc::Dataset ds("data/dataset.jsonl", "src/ml/labels.json");
    auto tr = ds.tensors(ds.indicesOf("train"), ds.standardizer());
    auto va = ds.tensors(ds.indicesOf("val"), ds.standardizer());

    nc::TrainConfig cfg;  // max 300 epochs, patience 25, class weights on

    nc::MLP model(ds.numFeatures(), ds.numClasses());
    auto res = nc::train(model, tr, va, ds.numClasses(), cfg, [](const nc::EpochStats& s) {
        if (s.epoch <= 10 || s.epoch % 5 == 0)
            std::printf("epoch %3d  train loss %.4f  val loss %.4f  val acc %5.1f%%\n",
                        s.epoch, s.train_loss, s.val_loss, 100 * s.val_accuracy);
    });

    std::printf("\nstopped after %d epochs, best epoch %d (val loss %.4f)\n",
                res.epochs_run, res.best_epoch, res.best_val_loss);

    auto r = nc::evaluate(model, va.x, va.y, ds.numClasses());
    std::printf("restored model: val loss %.4f, val accuracy %.1f%%\n", r.loss, 100 * r.accuracy);
    std::printf("\nconfusion matrix (rows = true, columns = predicted):\n");
    nc::printConfusion(r, ds.labels());
}