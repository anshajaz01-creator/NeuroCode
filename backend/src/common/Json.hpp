#pragma once
// JSON <-> C++ for the API. Field names mirror frontend/src/types/api.d.ts exactly.

#include <drogon/HttpResponse.h>
#include <nlohmann/json.hpp>

#include <cmath>
#include <string>
#include <variant>

#include "common/Errors.hpp"
#include "common/Types.hpp"

namespace nc {

inline double round4(double v) { return std::round(v * 10000.0) / 10000.0; }

// ---- engine types -> JSON --------------------------------------------------

inline void to_json(nlohmann::json& j, const AlgorithmGuess& g) {
    j = {{"label", g.label}, {"probability", round4(g.probability)}};
}
inline void to_json(nlohmann::json& j, const Complexity& c) {
    j = {{"time", c.time}, {"space", c.space}, {"derivation", c.derivation}};
}
inline void to_json(nlohmann::json& j, const Finding& f) {
    j = {{"line", f.line}, {"severity", f.severity}, {"type", f.type}, {"message", f.message}};
}
inline void to_json(nlohmann::json& j, const Counterexample& c) {
    j = {{"input", c.input}, {"expected_output", c.expected_output}, {"actual_output", c.actual_output}};
}
inline void to_json(nlohmann::json& j, const AnalysisResult& r) {
    j = {{"algorithms", r.algorithms},
         {"complexity", r.complexity},
         {"findings", r.findings},
         {"counterexamples", r.counterexamples},
         {"ast_json", r.ast_json},
         {"cfg_json", r.cfg_json},
         {"optimization_available", r.optimization_available},
         {"success", r.success},
         {"error", r.error}};
}
inline void to_json(nlohmann::json& j, const ProblemSpec& p) {
    j = {{"problem_id", p.problem_id},
         {"input_type", p.input_type},
         {"output_type", p.output_type},
         {"operation", p.operation},
         {"max_n", p.max_n}};
}
inline void to_json(nlohmann::json& j, const BenchmarkResult& b) {
    j = {{"before_ms", b.before_ms}, {"after_ms", b.after_ms},
         {"before_kb", b.before_kb}, {"after_kb", b.after_kb}, {"n_used", b.n_used}};
}
inline void to_json(nlohmann::json& j, const SummaryRow& r) {
    j = {{"label", r.label}, {"before", r.before}, {"after", r.after}};
}
inline void to_json(nlohmann::json& j, const OptimizationSummary& s) {
    j = {{"headline", s.headline}, {"explanation", s.explanation}, {"comparison", s.comparison},
         {"changes", s.changes}, {"tradeoff", s.tradeoff}, {"verification", s.verification},
         {"speedup", s.speedup}};
}
inline void to_json(nlohmann::json& j, const OptimizeResult& r) {
    j = {{"analysis", r.analysis},
         {"recommended_algorithm", r.recommended_algorithm},
         {"recommended_complexity", r.recommended_complexity},
         {"optimized_code", r.optimized_code},
         {"summary", r.summary},
         {"verified", r.verified},
         {"bench", r.bench},
         {"success", r.success},
         {"error", r.error}};
}

// ---- training / models / execute -> JSON -------------------------------------

inline void to_json(nlohmann::json& j, const EpochRecord& e) {
    j = {{"epoch", e.epoch}, {"train_loss", e.train_loss}, {"val_loss", e.val_loss},
         {"val_accuracy", e.val_accuracy}};
}
inline void to_json(nlohmann::json& j, const TrainSummary& t) {
    j = {{"version", t.version}, {"accuracy", t.accuracy}, {"loss", t.loss}, {"epochs", t.epochs},
         {"dataset_size", t.dataset_size}, {"history", t.history}};
}
inline void to_json(nlohmann::json& j, const ModelEntry& m) {
    j = {{"id", m.id},
         {"version", m.version},
         {"accuracy", m.accuracy},
         {"loss", m.loss ? nlohmann::json(*m.loss) : nlohmann::json(nullptr)},
         {"epochs", m.epochs},
         {"dataset_size", m.dataset_size},
         {"trained_at", m.trained_at},
         {"is_active", m.is_active}};
}
inline void to_json(nlohmann::json& j, const ExecuteOutcome& o) {
    j = {{"success", o.success}, {"compile_error", o.compile_error}, {"stdout", o.stdout_text},
         {"stderr", o.stderr_text}, {"exit_code", o.exit_code}, {"time_ms", o.time_ms},
         {"memory_kb", o.memory_kb}, {"timed_out", o.timed_out}};
}

// ---- Job -> JSON -----------------------------------------------------------

inline void to_json(nlohmann::json& j, const Job& job) {
    j = {{"id", job.id},
         {"type", toString(job.type)},
         {"status", toString(job.status)},
         {"problem_id", job.problem_id.empty() ? nlohmann::json(nullptr) : nlohmann::json(job.problem_id)},
         {"problem", job.type == JobType::Train ? nlohmann::json(nullptr) : nlohmann::json(job.problem)},
         {"input_code", job.input_code},
         {"progress", job.progress},
         {"stage", job.stage},
         {"error", job.error.empty() ? nlohmann::json(nullptr) : nlohmann::json(job.error)},
         {"created_at", job.created_at},
         {"finished_at", job.finished_at.empty() ? nlohmann::json(nullptr) : nlohmann::json(job.finished_at)}};

    nlohmann::json result = nullptr;
    std::visit(
        [&](const auto& r) {
            using T = std::decay_t<decltype(r)>;
            if constexpr (!std::is_same_v<T, std::monostate>) result = r;
        },
        job.result);
    j["result"] = std::move(result);
}

// ---- request validation ----------------------------------------------------

// Validates a ProblemSpec object from a request body. On failure returns false and sets err.
inline bool parseProblemSpec(const nlohmann::json& j, ProblemSpec& out, std::string& err) {
    if (!j.is_object()) { err = "problem must be an object"; return false; }

    auto str = [&](const char* key, bool required, std::string& dst) -> bool {
        auto it = j.find(key);
        if (it == j.end() || it->is_null()) {
            if (required) { err = std::string("problem.") + key + " is required"; return false; }
            dst.clear();
            return true;
        }
        if (!it->is_string()) { err = std::string("problem.") + key + " must be a string"; return false; }
        dst = it->get<std::string>();
        if (dst.size() > 64) { err = std::string("problem.") + key + " is too long (max 64)"; return false; }
        if (required && dst.empty()) { err = std::string("problem.") + key + " must not be empty"; return false; }
        return true;
    };

    ProblemSpec p;
    if (!str("problem_id", false, p.problem_id)) return false;
    if (!str("input_type", true, p.input_type)) return false;
    if (!str("output_type", true, p.output_type)) return false;
    if (!str("operation", true, p.operation)) return false;

    auto it = j.find("max_n");
    if (it == j.end() || !it->is_number_integer()) { err = "problem.max_n must be an integer"; return false; }
    const double n = it->get<double>();
    if (n < 1 || n > 1e9) { err = "problem.max_n must be between 1 and 1000000000"; return false; }
    p.max_n = it->get<long long>();

    out = std::move(p);
    return true;
}

// Validates a POST /models/train body. Every field is optional; missing ones keep their defaults.
inline bool parseTrainParams(const nlohmann::json& j, TrainParams& out, std::string& err) {
    if (!j.is_object()) { err = "body must be a JSON object"; return false; }
    TrainParams p;

    auto intField = [&](const char* key, int lo, int hi, int& dst) -> bool {
        auto it = j.find(key);
        if (it == j.end() || it->is_null()) return true;
        if (!it->is_number_integer()) { err = std::string(key) + " must be an integer"; return false; }
        const double v = it->get<double>();
        if (v < lo || v > hi) {
            err = std::string(key) + " must be between " + std::to_string(lo) + " and " + std::to_string(hi);
            return false;
        }
        dst = it->get<int>();
        return true;
    };

    if (!intField("epochs", 1, 2000, p.epochs)) return false;
    if (!intField("batch_size", 1, 4096, p.batch_size)) return false;
    if (!intField("early_stopping_patience", 1, 1000, p.early_stopping_patience)) return false;

    auto lr = j.find("learning_rate");
    if (lr != j.end() && !lr->is_null()) {
        if (!lr->is_number()) { err = "learning_rate must be a number"; return false; }
        const double v = lr->get<double>();
        if (!(v > 0.0 && v <= 1.0)) { err = "learning_rate must be greater than 0 and at most 1"; return false; }
        p.learning_rate = v;
    }
    out = p;
    return true;
}

// ---- HTTP helpers ----------------------------------------------------------

inline std::string dumpSafe(const nlohmann::json& j) {
    // 'replace' keeps invalid UTF-8 (e.g. program output) from throwing.
    return j.dump(-1, ' ', false, nlohmann::json::error_handler_t::replace);
}

inline drogon::HttpResponsePtr jsonResponse(const nlohmann::json& body,
                                            drogon::HttpStatusCode code = drogon::k200OK) {
    auto resp = drogon::HttpResponse::newHttpResponse();
    resp->setStatusCode(code);
    resp->setContentTypeCode(drogon::CT_APPLICATION_JSON);
    resp->setBody(dumpSafe(body));
    return resp;
}

inline drogon::HttpResponsePtr errorResponse(ErrorCode c, const std::string& message) {
    const ErrorInfo info = describe(c);
    return jsonResponse({{"error", {{"code", info.code}, {"message", message}}}},
                        static_cast<drogon::HttpStatusCode>(info.http));
}

}  // namespace nc
