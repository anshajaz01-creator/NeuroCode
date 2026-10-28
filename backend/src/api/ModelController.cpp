#include "api/ModelController.hpp"

#include "common/AppContext.hpp"
#include "common/Json.hpp"
#include "services/JobManager.hpp"
#include "services/ModelService.hpp"

namespace nc::api {

void ModelController::train(const drogon::HttpRequestPtr& req, Callback&& cb) const {
    auto& c = ctx();
    if (!c.jobs) return cb(errorResponse(ErrorCode::Internal, "job manager not ready"));
    if (!c.jobs->canTrain()) return cb(errorResponse(ErrorCode::NotImplemented, "training is not available on this server"));

    // An empty body means "all defaults".
    const std::string raw(req->body());
    nlohmann::json body = nlohmann::json::object();
    if (!raw.empty()) {
        body = nlohmann::json::parse(raw, nullptr, /*allow_exceptions=*/false);
        if (body.is_discarded()) return cb(errorResponse(ErrorCode::InvalidJson, "request body is not valid JSON"));
    }

    TrainParams params;
    std::string err;
    if (!parseTrainParams(body, params, err)) return cb(errorResponse(ErrorCode::ValidationFailed, err));

    const auto id = c.jobs->submitTrain(params);
    if (!id) return cb(errorResponse(ErrorCode::Conflict, "a training job is already queued or running"));
    cb(jsonResponse({{"job_id", *id}, {"status", "queued"}}, drogon::k202Accepted));
}

void ModelController::list(const drogon::HttpRequestPtr&, Callback&& cb) const {
    auto* models = ctx().models;
    if (!models) return cb(errorResponse(ErrorCode::Internal, "model service not ready"));
    cb(jsonResponse({{"models", models->list()}}));
}

void ModelController::activate(const drogon::HttpRequestPtr&, Callback&& cb, std::string&& idStr) const {
    auto* models = ctx().models;
    if (!models) return cb(errorResponse(ErrorCode::Internal, "model service not ready"));

    std::int64_t id = 0;
    if (!parseJobId(idStr, id)) return cb(errorResponse(ErrorCode::ValidationFailed, "invalid model id"));

    const auto r = models->activate(id);
    switch (r.status) {
        case ModelService::ActivateStatus::Ok:
            return cb(jsonResponse(*r.model));
        case ModelService::ActivateStatus::NotFound:
            return cb(errorResponse(ErrorCode::NotFound, "model not found"));
        case ModelService::ActivateStatus::NotAvailable:
            return cb(errorResponse(ErrorCode::NotImplemented, "model activation is not available yet"));
        case ModelService::ActivateStatus::LoadFailed:
            return cb(errorResponse(ErrorCode::Internal, "the model file could not be loaded"));
    }
}

}  // namespace nc::api
