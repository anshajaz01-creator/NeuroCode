#pragma once
// CORS, optional bearer-token check, and the /ws/jobs/{id} route rewrite.

#include <drogon/HttpRequest.h>

#include <string>

namespace nc::api {

// "Authorization: Bearer <token>", or ?token=<token> (browsers cannot set headers on WebSockets).
std::string extractToken(const drogon::HttpRequestPtr& req);

// Registers the advices on drogon::app(). Call after filling nc::ctx(), before run().
void installMiddleware();

}  // namespace nc::api
