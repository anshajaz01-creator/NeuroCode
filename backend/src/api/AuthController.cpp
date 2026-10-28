#include "api/AuthController.hpp"

#include "api/Middleware.hpp"
#include "common/AppContext.hpp"
#include "common/Json.hpp"
#include "services/AuthService.hpp"

namespace nc::api {

namespace {
nlohmann::json userJson(const AuthService& a) {
    return {{"id", a.userId()}, {"username", a.username()}};
}
}  // namespace

void AuthController::login(const drogon::HttpRequestPtr& req, Callback&& cb) const {
    auto* auth = ctx().auth;
    if (!auth) return cb(errorResponse(ErrorCode::Internal, "auth not ready"));

    const std::string raw(req->body());
    const nlohmann::json body = nlohmann::json::parse(raw, nullptr, false);
    if (body.is_discarded() || !body.is_object()) {
        return cb(errorResponse(ErrorCode::InvalidJson, "request body must be a JSON object"));
    }
    const auto u = body.find("username");
    const auto p = body.find("password");
    if (u == body.end() || !u->is_string() || p == body.end() || !p->is_string()) {
        return cb(errorResponse(ErrorCode::ValidationFailed, "username and password are required strings"));
    }

    const auto token = auth->login(u->get<std::string>(), p->get<std::string>());
    if (!token) return cb(errorResponse(ErrorCode::Unauthorized, "invalid username or password"));
    cb(jsonResponse({{"token", *token}, {"user", userJson(*auth)}}));
}

void AuthController::logout(const drogon::HttpRequestPtr& req, Callback&& cb) const {
    if (auto* auth = ctx().auth) auth->logout(extractToken(req));
    cb(jsonResponse({{"ok", true}}));
}

void AuthController::me(const drogon::HttpRequestPtr& req, Callback&& cb) const {
    auto* auth = ctx().auth;
    if (!auth || !auth->validate(extractToken(req))) {
        return cb(errorResponse(ErrorCode::Unauthorized, "missing or invalid token"));
    }
    cb(jsonResponse(userJson(*auth)));
}

void AuthController::signup(const drogon::HttpRequestPtr&, Callback&& cb) const {
    cb(errorResponse(ErrorCode::NotImplemented,
                     "signup is not available: this server has a single configured account"));
}

}  // namespace nc::api
