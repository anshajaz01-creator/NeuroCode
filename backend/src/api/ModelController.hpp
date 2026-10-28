#pragma once
// POST /api/v1/models/train            start a training job -> 202 {"job_id","status"}
// GET  /api/v1/models                  saved models -> {"models":[...]}
// POST /api/v1/models/{id}/activate    make a model the live one -> the ModelInfo
// Training progress (epoch events) arrives on /ws/jobs/{job_id}; the result is the job's result.

#include <drogon/HttpController.h>

#include <functional>
#include <string>

namespace nc::api {

class ModelController : public drogon::HttpController<ModelController> {
public:
    using Callback = std::function<void(const drogon::HttpResponsePtr&)>;

    METHOD_LIST_BEGIN
    ADD_METHOD_TO(ModelController::train, "/api/v1/models/train", drogon::Post);
    ADD_METHOD_TO(ModelController::list, "/api/v1/models", drogon::Get);
    ADD_METHOD_TO(ModelController::activate, "/api/v1/models/{1}/activate", drogon::Post);
    METHOD_LIST_END

    void train(const drogon::HttpRequestPtr& req, Callback&& cb) const;
    void list(const drogon::HttpRequestPtr& req, Callback&& cb) const;
    void activate(const drogon::HttpRequestPtr& req, Callback&& cb, std::string&& id) const;
};

}  // namespace nc::api
