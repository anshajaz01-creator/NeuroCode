#include "api/Middleware.hpp"

#include <drogon/drogon.h>

#include <algorithm>
#include <chrono>
#include <memory>

#include "common/AppContext.hpp"
#include "common/Json.hpp"
#include "services/AuthService.hpp"
#include "services/RateLimiter.hpp"

namespace nc::api {

namespace {

bool originAllowed(const std::string& origin) {
    const auto& allowed = ctx().corsOrigins;
    return std::any_of(allowed.begin(), allowed.end(),
                       [&](const std::string& o) { return o == "*" || o == origin; });
}

void addCors(const drogon::HttpRequestPtr& req, const drogon::HttpResponsePtr& resp) {
    const std::string origin = req->getHeader("origin");
    if (origin.empty() || !originAllowed(origin)) return;
    resp->addHeader("Access-Control-Allow-Origin", origin);
    resp->addHeader("Vary", "Origin");
    resp->addHeader("Access-Control-Allow-Methods", "GET, POST, DELETE, OPTIONS");
    resp->addHeader("Access-Control-Allow-Headers", "Content-Type, Authorization");
    resp->addHeader("Access-Control-Max-Age", "600");
}

bool isPublicPath(const std::string& path) {
    return path == "/api/v1/health" || path == "/api/v1/auth/login" || path == "/api/v1/auth/signup";
}

bool startsWith(const std::string& s, const char* prefix) { return s.rfind(prefix, 0) == 0; }

}  // namespace

std::string extractToken(const drogon::HttpRequestPtr& req) {
    const std::string h = req->getHeader("authorization");
    if (startsWith(h, "Bearer ")) return h.substr(7);
    return req->getParameter("token");
}

std::int64_t nowSeconds() {
    return std::chrono::duration_cast<std::chrono::seconds>(
               std::chrono::steady_clock::now().time_since_epoch()).count();
}

void installMiddleware() {
    using namespace drogon;

    // Only changes (POST/DELETE) are limited: the frontend polls GETs. Logins have their own,
    // tighter counter.
    auto writeLimiter = std::make_shared<RateLimiter>(ctx().writesPerMinute, 60);
    auto loginLimiter = std::make_shared<RateLimiter>(ctx().loginsPerMinute, 60);

    app().registerPreRoutingAdvice([writeLimiter, loginLimiter](const HttpRequestPtr& req, AdviceCallback&& stop,
                                                                 AdviceChainCallback&& next) {
        // 1. CORS preflight: answer here, before routing (most routes do not list OPTIONS).
        if (req->method() == Options && !req->getHeader("origin").empty()) {
            auto resp = HttpResponse::newHttpResponse();
            resp->setStatusCode(k204NoContent);
            addCors(req, resp);
            return stop(resp);
        }

        const std::string path = req->path();

        // 2. Rate limit on changes and on login attempts, per client IP.
        if ((req->method() == Post || req->method() == Delete) && startsWith(path, "/api/")) {
            const std::string ip = req->peerAddr().toIp();
            int wait = 0;
            if (path == "/api/v1/auth/login") wait = loginLimiter->check(ip, nowSeconds());
            if (wait == 0) wait = writeLimiter->check(ip, nowSeconds());
            if (wait > 0) {
                auto resp = errorResponse(ErrorCode::TooManyRequests,
                                          "too many requests, retry in " + std::to_string(wait) + " s");
                resp->addHeader("Retry-After", std::to_string(wait));
                addCors(req, resp);
                return stop(resp);
            }
        }

        // 3. Token check, only when auth.required is true in config.json.
        const bool guarded = ctx().authRequired && (startsWith(path, "/api/") || startsWith(path, "/ws/"));
        if (guarded && !isPublicPath(path) &&
            !(ctx().auth && ctx().auth->validate(extractToken(req)))) {
            auto resp = errorResponse(ErrorCode::Unauthorized, "missing or invalid token");
            addCors(req, resp);
            return stop(resp);
        }

        // 4. Drogon WebSocket routes cannot have path parameters, so /ws/jobs/{id}
        //    is rewritten to /ws/jobs with the id passed as the job_id parameter.
        static const std::string wsPrefix = "/ws/jobs/";
        if (startsWith(path, wsPrefix.c_str()) && path.size() > wsPrefix.size()) {
            req->setParameter("job_id", path.substr(wsPrefix.size()));
            req->setPath("/ws/jobs");
        }
        next();
    });

    app().registerPreSendingAdvice([](const HttpRequestPtr& req, const HttpResponsePtr& resp) {
        addCors(req, resp);
    });
}

}  // namespace nc::api
