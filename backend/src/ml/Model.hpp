#pragma once
#include <torch/torch.h>

namespace nc {

// n_features -> 128 -> ReLU -> Dropout(0.3) -> 64 -> ReLU -> Dropout(0.2) -> n_classes
// forward() returns raw logits; softmax is applied only when predicting.
struct MLPImpl : torch::nn::Module {
    MLPImpl(int64_t n_features, int64_t n_classes);
    torch::Tensor forward(torch::Tensor x);

    torch::nn::Linear fc1{nullptr}, fc2{nullptr}, fc3{nullptr};
    torch::nn::Dropout drop1{nullptr}, drop2{nullptr};
};
TORCH_MODULE(MLP);

}  // namespace nc