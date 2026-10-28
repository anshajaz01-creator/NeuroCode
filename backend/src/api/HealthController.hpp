#pragma once
// GET /api/v1/health
// Response: {"status":"ok","db":"ok","model_loaded":true}
//
// db / model_loaded come from probes that main.cpp registers once the
// database and predictor exist. Until then they report "not_configured" / false.
// Set the probes BEFORE drogon::app().run(); they are read-only afterwards.

#include <drogon/HttpController.h>

#include <functional>

namespace nc::api {

class HealthController : public drogon::HttpController<HealthController> {
public:
    using Probe = std::function<bool()>;

    static void setDbProbe(Probe probe);
    static void setModelProbe(Probe probe);

    METHOD_LIST_BEGIN
    ADD_METHOD_TO(HealthController::health, "/api/v1/health", drogon::Get);
    METHOD_LIST_END

    void health(const drogon::HttpRequestPtr& req,
                std::function<void(const drogon::HttpResponsePtr&)>&& callback) const;
};

}  // namespace nc::api
