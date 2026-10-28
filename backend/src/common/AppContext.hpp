#pragma once
// Process-wide handles to the services. main.cpp fills this in BEFORE drogon::app().run();
// controllers read it per request. Drogon creates controllers itself, so they cannot take
// constructor arguments.

#include <cstddef>
#include <string>
#include <vector>

namespace nc {

class JobManager;
class ProgressBroadcaster;
class AuthService;
class ProblemCatalog;
class CodeExecutor;
class ModelService;

struct AppContext {
    JobManager* jobs = nullptr;
    ProgressBroadcaster* broadcaster = nullptr;
    AuthService* auth = nullptr;
    ProblemCatalog* problems = nullptr;
    CodeExecutor* executor = nullptr;
    ModelService* models = nullptr;

    std::size_t maxCodeBytes = 65536;
    std::size_t maxStdinBytes = 65536;
    int writesPerMinute = 60;               // POST/DELETE per client IP; 0 turns the limit off
    int loginsPerMinute = 10;               // login attempts per client IP
    bool authRequired = false;
    std::vector<std::string> corsOrigins;   // "*" allows any origin
};

inline AppContext& ctx() {
    static AppContext c;
    return c;
}

}  // namespace nc
