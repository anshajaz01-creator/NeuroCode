#pragma once
// Fans job progress out to the WebSocket clients watching that job.
// Event shapes match WsEvent in frontend/src/types/api.d.ts.

#include <drogon/WebSocketConnection.h>
#include <nlohmann/json.hpp>

#include <cstdint>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

namespace nc {

class ProgressBroadcaster {
public:
    using Conn = drogon::WebSocketConnectionPtr;

    void subscribe(std::int64_t jobId, const Conn& conn);
    void unsubscribe(std::int64_t jobId, const Conn& conn);

    void publishProgress(std::int64_t jobId, int percent, const std::string& stage);
    void publishEpoch(std::int64_t jobId, int epoch, double trainLoss, double valLoss, double valAccuracy);
    // Terminal events: sent to every subscriber, which are then closed and forgotten.
    void publishDone(std::int64_t jobId);
    void publishError(std::int64_t jobId, const std::string& message);

    static std::string progressEvent(int percent, const std::string& stage);
    static std::string doneEvent();
    static std::string errorEvent(const std::string& message);

private:
    void publish(std::int64_t jobId, const std::string& payload, bool terminal);

    std::mutex mu_;
    std::unordered_map<std::int64_t, std::vector<Conn>> subs_;
};

}  // namespace nc
