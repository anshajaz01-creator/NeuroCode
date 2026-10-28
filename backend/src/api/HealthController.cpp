#include "api/HealthController.hpp"

#include <nlohmann/json.hpp>

namespace nc::api {

namespace {
HealthController::Probe g_dbProbe;     // empty until the Database exists
HealthController::Probe g_modelProbe;  // empty until the Predictor exists
}  // namespace

void HealthController::setDbProbe(Probe probe) { g_dbProbe = std::move(probe); }
void HealthController::setModelProbe(Probe probe) { g_modelProbe = std::move(probe); }

void HealthController::health(
    const drogon::HttpRequestPtr& /*req*/,
    std::function<void(const drogon::HttpResponsePtr&)>&& callback) const {
    std::string db = "not_configured";
    if (g_dbProbe) db = g_dbProbe() ? "ok" : "error";

    const bool modelLoaded = g_modelProbe ? g_modelProbe() : false;
    const bool degraded = (db == "error");

    nlohmann::json body = {
        {"status", degraded ? "degraded" : "ok"},
        {"db", db},
        {"model_loaded", modelLoaded},
    };

    auto resp = drogon::HttpResponse::newHttpResponse();
    resp->setStatusCode(degraded ? drogon::k503ServiceUnavailable : drogon::k200OK);
    resp->setContentTypeCode(drogon::CT_APPLICATION_JSON);
    resp->setBody(body.dump());
    callback(resp);
}

}  // namespace nc::api
