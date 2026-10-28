#include "api/ProblemController.hpp"

#include "common/AppContext.hpp"
#include "common/Json.hpp"
#include "services/ProblemCatalog.hpp"

namespace nc::api {

namespace {

nlohmann::json toJson(const Problem& p) {
    return {{"id", p.id},
            {"title", p.title},
            {"input_type", p.input_type},
            {"output_type", p.output_type},
            {"operation", p.operation},
            {"max_n", p.max_n},
            {"optimal_time", p.optimal_time},
            {"description", p.description}};
}

}  // namespace

void ProblemController::list(const drogon::HttpRequestPtr&, Callback&& cb) const {
    auto* catalog = ctx().problems;
    if (!catalog) return cb(errorResponse(ErrorCode::Internal, "catalog not ready"));

    nlohmann::json arr = nlohmann::json::array();
    for (const auto& p : catalog->all()) arr.push_back(toJson(p));
    cb(jsonResponse({{"problems", std::move(arr)}}));
}

void ProblemController::get(const drogon::HttpRequestPtr&, Callback&& cb, std::string&& id) const {
    auto* catalog = ctx().problems;
    if (!catalog) return cb(errorResponse(ErrorCode::Internal, "catalog not ready"));

    const Problem* p = catalog->find(id);
    if (!p) return cb(errorResponse(ErrorCode::NotFound, "problem not found"));
    cb(jsonResponse(toJson(*p)));
}

}  // namespace nc::api
