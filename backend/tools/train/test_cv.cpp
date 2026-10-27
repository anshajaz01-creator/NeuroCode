#include <cstdio>

#include "ml/Dataset.hpp"
#include "ml/Metrics.hpp"
#include "ml/Trainer.hpp"

int main() {
    nc::Dataset ds("data/dataset.jsonl", "src/ml/labels.json");
    nc::TrainConfig cfg;  // defaults: patience 25, class weights on

    std::printf("grouped 5-fold cross-validation, %zu samples\n", ds.rows().size());
    auto cv = nc::crossValidate(ds, 5, cfg);

    for (size_t f = 0; f < cv.fold_accuracy.size(); ++f)
        std::printf("  fold %zu: test acc %5.1f%%  (best epoch %d)\n", f + 1,
                    100 * cv.fold_accuracy[f], cv.fold_best_epoch[f]);

    std::printf("\nMLP CV accuracy: %.1f%%   (linear baseline: 84.2%%)\n\n", 100 * cv.accuracy);
    nc::printPerClass(cv.pooled, ds.labels());
    std::printf("\npooled confusion matrix (rows = true, columns = predicted):\n");
    nc::printConfusion(cv.pooled, ds.labels());
}