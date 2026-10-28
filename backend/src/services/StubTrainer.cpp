#include "services/StubTrainer.hpp"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <ctime>
#include <thread>

namespace nc {

TrainFn makeStubTrainFn() {
    return [](const TrainParams& params, const EpochSink& onEpoch) {
        TrainSummary s;
        const int epochs = std::min(params.epochs, 20);   // keep the fake run short (~3 s)
        for (int e = 1; e <= epochs; ++e) {
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
            const double t = static_cast<double>(e) / epochs;
            EpochRecord r;
            r.epoch = e;
            r.train_loss = 1.8 * std::exp(-3.0 * t) + 0.20;
            r.val_loss = 1.9 * std::exp(-2.6 * t) + 0.28;
            r.val_accuracy = 0.45 + 0.40 * (1.0 - std::exp(-3.0 * t));
            onEpoch(r);          // throws TrainCancelled when the job is cancelled
            s.history.push_back(r);
        }
        char buf[32];
        const std::time_t now = std::time(nullptr);
        std::tm tm{};
        gmtime_r(&now, &tm);
        std::strftime(buf, sizeof(buf), "stub-%Y%m%d-%H%M%S", &tm);
        s.version = buf;
        s.epochs = epochs;
        s.dataset_size = 2067;
        if (!s.history.empty()) {
            s.accuracy = s.history.back().val_accuracy;
            s.loss = s.history.back().val_loss;
        }
        return s;
    };
}

}  // namespace nc
