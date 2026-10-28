#include "services/ProgressBroadcaster.hpp"

#include <algorithm>

#include "common/Json.hpp"

namespace nc {

std::string ProgressBroadcaster::progressEvent(int percent, const std::string& stage) {
    return dumpSafe({{"type", "progress"}, {"percent", percent}, {"stage", stage}});
}
std::string ProgressBroadcaster::doneEvent() { return dumpSafe({{"type", "done"}}); }
std::string ProgressBroadcaster::errorEvent(const std::string& message) {
    return dumpSafe({{"type", "error"}, {"message", message}});
}

void ProgressBroadcaster::subscribe(std::int64_t jobId, const Conn& conn) {
    std::lock_guard<std::mutex> lk(mu_);
    subs_[jobId].push_back(conn);
}

void ProgressBroadcaster::unsubscribe(std::int64_t jobId, const Conn& conn) {
    std::lock_guard<std::mutex> lk(mu_);
    auto it = subs_.find(jobId);
    if (it == subs_.end()) return;
    auto& v = it->second;
    v.erase(std::remove(v.begin(), v.end(), conn), v.end());
    if (v.empty()) subs_.erase(it);
}

void ProgressBroadcaster::publishProgress(std::int64_t jobId, int percent, const std::string& stage) {
    publish(jobId, progressEvent(percent, stage), false);
}

void ProgressBroadcaster::publishEpoch(std::int64_t jobId, int epoch, double trainLoss,
                                       double valLoss, double valAccuracy) {
    publish(jobId,
            dumpSafe({{"type", "epoch"}, {"epoch", epoch}, {"train_loss", trainLoss},
                      {"val_loss", valLoss}, {"val_accuracy", valAccuracy}}),
            false);
}

void ProgressBroadcaster::publishDone(std::int64_t jobId) { publish(jobId, doneEvent(), true); }

void ProgressBroadcaster::publishError(std::int64_t jobId, const std::string& message) {
    publish(jobId, errorEvent(message), true);
}

void ProgressBroadcaster::publish(std::int64_t jobId, const std::string& payload, bool terminal) {
    std::vector<Conn> targets;
    {
        std::lock_guard<std::mutex> lk(mu_);
        auto it = subs_.find(jobId);
        if (it == subs_.end()) return;
        targets = it->second;
        if (terminal) subs_.erase(it);
    }
    // Sent outside the lock: a slow client must not block the engine thread or other jobs.
    for (const auto& c : targets) {
        if (!c->connected()) continue;
        c->send(payload);
        if (terminal) c->shutdown(drogon::CloseCode::kNormalClosure, "job finished");
    }
}

}  // namespace nc
