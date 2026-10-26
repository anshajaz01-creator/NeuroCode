#pragma once
#include <filesystem>
#include <stdexcept>
#include <string>
#include <system_error>
#include <unistd.h>

namespace nc {

// A private per-job directory, removed with everything in it when it goes out of scope.
// Pass the uid the sandbox will run as (Limits::run_as_uid) so that user can write to it.
class ScratchDir {
public:
    explicit ScratchDir(int owner_uid = -1, const std::string& base = "/tmp") {
        std::string tmpl = base + "/neurocode-XXXXXX";
        if (!mkdtemp(tmpl.data())) throw std::runtime_error("mkdtemp failed for " + tmpl);
        path_ = tmpl;
        if (owner_uid >= 0 && geteuid() == 0 && chown(path_.c_str(), static_cast<uid_t>(owner_uid), static_cast<gid_t>(owner_uid)) != 0)
            throw std::runtime_error("chown failed for " + path_);
    }
    ScratchDir(const ScratchDir&) = delete;
    ScratchDir& operator=(const ScratchDir&) = delete;
    ~ScratchDir() { std::error_code ec; std::filesystem::remove_all(path_, ec); }

    const std::string& path() const { return path_; }

private:
    std::string path_;
};

} // namespace nc
