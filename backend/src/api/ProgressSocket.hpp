#pragma once
// WS /ws/jobs/{id}: live progress for one job.
// Events (WsEvent in api.d.ts): {"type":"progress","percent","stage"}, {"type":"done"},
// {"type":"error","message"}. The server closes the socket after done/error.
// Middleware rewrites /ws/jobs/{id} to /ws/jobs?job_id={id}; see Middleware.cpp.

#include <drogon/WebSocketController.h>

#include <string>

namespace nc::api {

class ProgressSocket : public drogon::WebSocketController<ProgressSocket> {
public:
    void handleNewConnection(const drogon::HttpRequestPtr& req,
                             const drogon::WebSocketConnectionPtr& conn) override;
    void handleNewMessage(const drogon::WebSocketConnectionPtr& conn, std::string&& message,
                          const drogon::WebSocketMessageType& type) override;
    void handleConnectionClosed(const drogon::WebSocketConnectionPtr& conn) override;

    WS_PATH_LIST_BEGIN
    WS_PATH_ADD("/ws/jobs");
    WS_PATH_LIST_END
};

}  // namespace nc::api
