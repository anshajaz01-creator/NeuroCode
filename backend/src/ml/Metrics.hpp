#pragma once
#include <string>
#include <vector>

#include <torch/torch.h>

#include "ml/Model.hpp"

namespace nc {

struct EvalResult {
    double loss = 0.0;
    double accuracy = 0.0;
    std::vector<std::vector<int64_t>> confusion;  // [true class][predicted class]
    std::vector<double> per_class_accuracy;       // -1 if a class has no samples
    std::vector<int64_t> per_class_count;
};

// Runs the model in eval mode (no dropout, no gradients) over x/y.
EvalResult evaluate(MLP& model, const torch::Tensor& x, const torch::Tensor& y, int n_classes);

void printPerClass(const EvalResult& r, const std::vector<std::string>& labels);
void printConfusion(const EvalResult& r, const std::vector<std::string>& labels);

}  // namespace nc