#pragma once
// POST /api/v1/execute  {code, stdin} -> ExecuteResponse (api.d.ts)
// "Synchronous" for the client: the response comes when the run finishes. On the server it
// runs on CodeExecutor's own workers, never on a Drogon IO thread.
// 200 even for a compile error (success:false); 503 busy when too many runs are waiting.

#include <drogon/HttpController.h>

#include <functional>

namespace nc::api {

class ExecuteController : public drogon::HttpController<ExecuteController> {
public:
    using Callback = std::function<void(const drogon::HttpResponsePtr&)>;

    METHOD_LIST_BEGIN
    ADD_METHOD_TO(ExecuteController::execute, "/api/v1/execute", drogon::Post);
    METHOD_LIST_END

    void execute(const drogon::HttpRequestPtr& req, Callback&& cb) const;
};

}  // namespace nc::api
