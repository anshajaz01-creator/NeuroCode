#include "ml/Model.hpp"

namespace nc {

MLPImpl::MLPImpl(int64_t n_features, int64_t n_classes) {
    fc1 = register_module("fc1", torch::nn::Linear(n_features, 128));
    fc2 = register_module("fc2", torch::nn::Linear(128, 64));
    fc3 = register_module("fc3", torch::nn::Linear(64, n_classes));
    drop1 = register_module("drop1", torch::nn::Dropout(0.3));
    drop2 = register_module("drop2", torch::nn::Dropout(0.2));
}

torch::Tensor MLPImpl::forward(torch::Tensor x) {
    x = drop1(torch::relu(fc1(x)));
    x = drop2(torch::relu(fc2(x)));
    return fc3(x);  // logits: no softmax here
}

}  // namespace nc