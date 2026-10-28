#pragma once
// POST /api/v1/auth/login    {username,password} -> {token, user}
// POST /api/v1/auth/logout   invalidates the bearer token
// GET  /api/v1/auth/me       current user
// POST /api/v1/auth/signup   501: single hardcoded account, no database

#include <drogon/HttpController.h>

#include <functional>

namespace nc::api {

class AuthController : public drogon::HttpController<AuthController> {
public:
    using Callback = std::function<void(const drogon::HttpResponsePtr&)>;

    METHOD_LIST_BEGIN
    ADD_METHOD_TO(AuthController::login, "/api/v1/auth/login", drogon::Post);
    ADD_METHOD_TO(AuthController::logout, "/api/v1/auth/logout", drogon::Post);
    ADD_METHOD_TO(AuthController::me, "/api/v1/auth/me", drogon::Get);
    ADD_METHOD_TO(AuthController::signup, "/api/v1/auth/signup", drogon::Post);
    METHOD_LIST_END

    void login(const drogon::HttpRequestPtr& req, Callback&& cb) const;
    void logout(const drogon::HttpRequestPtr& req, Callback&& cb) const;
    void me(const drogon::HttpRequestPtr& req, Callback&& cb) const;
    void signup(const drogon::HttpRequestPtr& req, Callback&& cb) const;
};

}  // namespace nc::api
