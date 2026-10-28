#pragma once
// Lists the checkpoints in the models directory and tracks which one is active.
// No database: each model is a pair <name>.pt + <name>.json (ModelInfo, written by T1's
// saveCheckpoint), and the active one is remembered in a one-line <dir>/ACTIVE file.

#include <cstdint>
#include <functional>
#include <mutex>
#include <optional>
#include <string>
#include <vector>

#include "common/Types.hpp"

namespace nc {

class ModelService {
public:
    // Loads the weights into the live predictor. Gets the full path of the .pt file;
    // returns false if it could not be loaded. Empty until T1's Predictor is wired in.
    using LoadFn = std::function<bool(const std::string& pt_path)>;

    enum class ActivateStatus { Ok, NotFound, NotAvailable, LoadFailed };
    struct ActivateResult {
        ActivateStatus status = ActivateStatus::NotFound;
        std::optional<ModelEntry> model;
    };

    ModelService(std::string modelsDir, LoadFn load);

    // Sorted by trained_at, oldest first. Checkpoints with a missing .pt or an unreadable
    // .json are skipped.
    std::vector<ModelEntry> list() const;
    ActivateResult activate(std::int64_t id);
    // Re-loads the model named in ACTIVE (call once at startup). False if none or it failed.
    bool restoreActive();
    bool canActivate() const { return static_cast<bool>(load_); }

private:
    struct Found {
        ModelEntry entry;
        std::string stem;      // file name without extension
        std::string ptPath;
    };

    std::vector<Found> scan() const;
    std::string readActiveStem() const;
    void writeActiveStem(const std::string& stem) const;

    std::string dir_;
    LoadFn load_;
    mutable std::mutex mu_;
};

}  // namespace nc
