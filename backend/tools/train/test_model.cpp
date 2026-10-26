#include <cstdio>

#include "ml/Dataset.hpp"
#include "ml/Model.hpp"

int main() {
    torch::manual_seed(42);
    nc::Dataset ds("data/dataset.jsonl", "src/ml/labels.json");
    nc::MLP model(ds.numFeatures(), ds.numClasses());

    // 1. size of the network
    int64_t n_params = 0;
    for (const auto& p : model->parameters()) n_params += p.numel();
    std::printf("parameters: %lld\n", (long long)n_params);

    // 2. one forward pass on the first 5 training rows
    auto tr = ds.tensors(ds.indicesOf("train"), ds.standardizer());
    auto x5 = tr.x.slice(0, 0, 5);  // rows 0..4
    model->eval();
    auto logits = model->forward(x5);
    std::printf("logits shape: %s\n", c10::str(logits.sizes()).c_str());

    auto probs = torch::softmax(logits, 1);
    for (int i = 0; i < 5; ++i) {
        int64_t pred = probs[i].argmax().item<int64_t>();
        std::printf("  row %d: predicted %-24s p=%.3f  (true: %s)  row prob sum %.3f\n", i,
                    ds.labels()[pred].c_str(), probs[i][pred].item<float>(),
                    ds.labels()[tr.y[i].item<int64_t>()].c_str(), probs[i].sum().item<float>());
    }

    // 3. dropout: random in train mode, off in eval mode
    model->train();
    bool train_same = torch::equal(model->forward(x5), model->forward(x5));
    model->eval();
    bool eval_same = torch::equal(model->forward(x5), model->forward(x5));
    std::printf("two forward passes identical?  train mode: %s   eval mode: %s\n",
                train_same ? "yes" : "no", eval_same ? "yes" : "no");
}