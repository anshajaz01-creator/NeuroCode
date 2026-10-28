#pragma once
// GET /api/v1/problems        catalog for the problem picker -> {"problems":[...]}
// GET /api/v1/problems/{id}   one problem

#include <drogon/HttpController.h>

#include <functional>
#include <string>

namespace nc::api {

class ProblemController : public drogon::HttpController<ProblemController> {
public:
    using Callback = std::function<void(const drogon::HttpResponsePtr&)>;

    METHOD_LIST_BEGIN
    ADD_METHOD_TO(ProblemController::list, "/api/v1/problems", drogon::Get);
    ADD_METHOD_TO(ProblemController::get, "/api/v1/problems/{1}", drogon::Get);
    METHOD_LIST_END

    void list(const drogon::HttpRequestPtr& req, Callback&& cb) const;
    void get(const drogon::HttpRequestPtr& req, Callback&& cb, std::string&& id) const;
};

}  // namespace nc::api
