#include "api/ExecuteController.hpp"

#include <memory>

#include "common/AppContext.hpp"
#include "common/Json.hpp"
#include "services/CodeExecutor.hpp"

namespace nc::api {

void ExecuteController::execute(const drogon::HttpRequestPtr& req, Callback&& cb) const {
    auto& c = ctx();
    if (!c.executor) return cb(errorResponse(ErrorCode::NotImplemented, "code execution is not available"));

    const std::string raw(req->body());
    const nlohmann::json body = nlohmann::json::parse(raw, nullptr, /*allow_exceptions=*/false);
    if (body.is_discarded() || !body.is_object()) {
        return cb(errorResponse(ErrorCode::InvalidJson, "request body must be a JSON object"));
    }

    auto codeIt = body.find("code");
    if (codeIt == body.end() || !codeIt->is_string() || codeIt->get<std::string>().empty()) {
        return cb(errorResponse(ErrorCode::ValidationFailed, "code is required and must be a non-empty string"));
    }
    ExecuteRequest er;
    er.code = codeIt->get<std::string>();
    if (er.code.size() > c.maxCodeBytes) {
        return cb(errorResponse(ErrorCode::PayloadTooLarge,
                                "code is larger than " + std::to_string(c.maxCodeBytes) + " bytes"));
    }

    auto stdinIt = body.find("stdin");
    if (stdinIt != body.end() && !stdinIt->is_null()) {
        if (!stdinIt->is_string()) return cb(errorResponse(ErrorCode::ValidationFailed, "stdin must be a string"));
        er.stdin_text = stdinIt->get<std::string>();
        if (er.stdin_text.size() > c.maxStdinBytes) {
            return cb(errorResponse(ErrorCode::PayloadTooLarge,
                                    "stdin is larger than " + std::to_string(c.maxStdinBytes) + " bytes"));
        }
    }

    // The reply is sent from a worker thread; Drogon allows calling the callback from any thread.
    auto reply = std::make_shared<Callback>(std::move(cb));
    const bool accepted = c.executor->submit(std::move(er), [reply](ExecuteOutcome out) {
        (*reply)(jsonResponse(out));
    });
    if (!accepted) {
        (*reply)(errorResponse(ErrorCode::Busy, "the sandbox is busy, try again in a moment"));
    }
}

}  // namespace nc::api
