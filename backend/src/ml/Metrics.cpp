#include "ml/Metrics.hpp"

#include <cstdio>

namespace nc {

EvalResult evaluate(MLP& model, const torch::Tensor& x, const torch::Tensor& y, int n_classes) {
    EvalResult r;
    r.confusion.assign(n_classes, std::vector<int64_t>(n_classes, 0));
    r.per_class_accuracy.assign(n_classes, -1.0);
    r.per_class_count.assign(n_classes, 0);
    if (!y.defined() || y.size(0) == 0) return r;

    torch::NoGradGuard no_grad;   // measuring only: don't track gradients
    model->eval();                // dropout off
    auto logits = model->forward(x);

    r.loss = torch::nn::functional::cross_entropy(logits, y).item<double>();
    auto pred = logits.argmax(1);  // highest score per row = predicted class
    r.accuracy = pred.eq(y).to(torch::kFloat64).mean().item<double>();

    // confusion matrix: count (true, predicted) pairs
    auto yp = y.accessor<int64_t, 1>();
    auto pp = pred.accessor<int64_t, 1>();
    for (int64_t i = 0; i < y.size(0); ++i) r.confusion[yp[i]][pp[i]]++;

    // per-class accuracy: diagonal / row total
    for (int c = 0; c < n_classes; ++c) {
        int64_t total = 0;
        for (int p = 0; p < n_classes; ++p) total += r.confusion[c][p];
        r.per_class_count[c] = total;
        if (total > 0) r.per_class_accuracy[c] = static_cast<double>(r.confusion[c][c]) / total;
    }
    return r;
}

void printPerClass(const EvalResult& r, const std::vector<std::string>& labels) {
    std::printf("  %-26s %6s %9s\n", "label", "n", "accuracy");
    for (size_t c = 0; c < labels.size(); ++c) {
        if (r.per_class_accuracy[c] < 0)
            std::printf("  %-26s %6lld %9s\n", labels[c].c_str(), (long long)r.per_class_count[c], "-");
        else
            std::printf("  %-26s %6lld %8.0f%%\n", labels[c].c_str(), (long long)r.per_class_count[c],
                        100.0 * r.per_class_accuracy[c]);
    }
}

void printConfusion(const EvalResult& r, const std::vector<std::string>& labels) {
    // rows = true class, columns = predicted class, labels cut to 4 chars
    std::printf("  %-6s", "t\\p");
    for (const auto& l : labels) std::printf("%5.4s", l.c_str());
    std::printf("\n");
    for (size_t t = 0; t < labels.size(); ++t) {
        std::printf("  %-6.4s", labels[t].c_str());
        for (size_t p = 0; p < labels.size(); ++p) {
            if (r.confusion[t][p] == 0) std::printf("%5s", ".");
            else std::printf("%5lld", (long long)r.confusion[t][p]);
        }
        std::printf("\n");
    }
}

}  // namespace nc