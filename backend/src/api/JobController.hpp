#pragma once
// POST   /api/v1/jobs        create an analyze/optimize job -> 202 {"job_id", "status"}
// GET    /api/v1/jobs        history (newest first, no results)
// GET    /api/v1/jobs/{id}   status + result
// DELETE /api/v1/jobs/{id}   cancel

#include <drogon/HttpController.h>

#include <functional>
#include <string>

namespace nc::api {

class JobController : public drogon::HttpController<JobController> {
public:
    using Callback = std::function<void(const drogon::HttpResponsePtr&)>;

    METHOD_LIST_BEGIN
    ADD_METHOD_TO(JobController::create, "/api/v1/jobs", drogon::Post);
    ADD_METHOD_TO(JobController::list, "/api/v1/jobs", drogon::Get);
    ADD_METHOD_TO(JobController::get, "/api/v1/jobs/{1}", drogon::Get);
    ADD_METHOD_TO(JobController::cancel, "/api/v1/jobs/{1}", drogon::Delete);
    METHOD_LIST_END

    void create(const drogon::HttpRequestPtr& req, Callback&& cb) const;
    void list(const drogon::HttpRequestPtr& req, Callback&& cb) const;
    void get(const drogon::HttpRequestPtr& req, Callback&& cb, std::string&& id) const;
    void cancel(const drogon::HttpRequestPtr& req, Callback&& cb, std::string&& id) const;
};

}  // namespace nc::api
