#include "api/ProgressSocket.hpp"

#include <cstdint>
#include <memory>

#include "common/AppContext.hpp"
#include "common/Types.hpp"
#include "services/JobManager.hpp"
#include "services/ProgressBroadcaster.hpp"

namespace nc::api {

namespace {
void rejectAndClose(const drogon::WebSocketConnectionPtr& conn, const std::string& message) {
    conn->send(ProgressBroadcaster::errorEvent(message));
    conn->shutdown(drogon::CloseCode::kViolation, message);
}
}  // namespace

void ProgressSocket::handleNewConnection(const drogon::HttpRequestPtr& req,
                                         const drogon::WebSocketConnectionPtr& conn) {
    auto& c = ctx();
    std::int64_t id = 0;
    if (!c.jobs || !c.broadcaster) return rejectAndClose(conn, "server not ready");
    if (!parseJobId(req->getParameter("job_id"), id)) return rejectAndClose(conn, "invalid job id");

    // Subscribe first, then read the current state: an event that lands in between is
    // delivered twice at worst, never lost.
    c.broadcaster->subscribe(id, conn);
    conn->setContext(std::make_shared<std::int64_t>(id));

    const auto job = c.jobs->get(id);
    if (!job) {
        c.broadcaster->unsubscribe(id, conn);
        return rejectAndClose(conn, "job not found");
    }

    switch (job->status) {
        case JobStatus::Queued:
        case JobStatus::Running:
            conn->send(ProgressBroadcaster::progressEvent(job->progress, job->stage));
            break;
        case JobStatus::Done:
            conn->send(ProgressBroadcaster::progressEvent(100, "complete"));
            conn->send(ProgressBroadcaster::doneEvent());
            c.broadcaster->unsubscribe(id, conn);
            conn->shutdown(drogon::CloseCode::kNormalClosure, "job finished");
            break;
        case JobStatus::Failed:
        case JobStatus::Cancelled:
            conn->send(ProgressBroadcaster::errorEvent(job->error));
            c.broadcaster->unsubscribe(id, conn);
            conn->shutdown(drogon::CloseCode::kNormalClosure, "job finished");
            break;
    }
}

void ProgressSocket::handleNewMessage(const drogon::WebSocketConnectionPtr&, std::string&&,
                                      const drogon::WebSocketMessageType&) {
    // Server-to-client only. Ping/pong is handled by Drogon.
}

void ProgressSocket::handleConnectionClosed(const drogon::WebSocketConnectionPtr& conn) {
    auto id = conn->getContext<std::int64_t>();
    if (id && ctx().broadcaster) ctx().broadcaster->unsubscribe(*id, conn);
}

}  // namespace nc::api
