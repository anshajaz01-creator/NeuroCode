#include "services/ModelService.hpp"

#include <algorithm>
#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

#include "common/Logger.hpp"

namespace fs = std::filesystem;

namespace nc {

namespace {

// Stable id from the version string, so ids do not shift when models are added or removed.
std::int64_t idFor(const std::string& version) {
    std::uint32_t h = 2166136261u;   // FNV-1a
    for (const unsigned char c : version) {
        h ^= c;
        h *= 16777619u;
    }
    return static_cast<std::int64_t>(h) + 1;   // > 0, fits a JS number
}

std::string isoFromFileTime(const fs::file_time_type& ft) {
    const auto sys = std::chrono::clock_cast<std::chrono::system_clock>(ft);
    const std::time_t t = std::chrono::system_clock::to_time_t(sys);
    std::tm tm{};
    gmtime_r(&t, &tm);
    char buf[32];
    std::strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%SZ", &tm);
    return buf;
}

}  // namespace

ModelService::ModelService(std::string modelsDir, LoadFn load)
    : dir_(std::move(modelsDir)), load_(std::move(load)) {}

std::string ModelService::readActiveStem() const {
    std::ifstream in(fs::path(dir_) / "ACTIVE");
    std::string stem;
    std::getline(in, stem);
    while (!stem.empty() && (stem.back() == '\r' || stem.back() == ' ')) stem.pop_back();
    return stem;
}

void ModelService::writeActiveStem(const std::string& stem) const {
    std::ofstream out(fs::path(dir_) / "ACTIVE", std::ios::trunc);
    out << stem << "\n";
}

std::vector<ModelService::Found> ModelService::scan() const {
    std::vector<Found> out;
    std::error_code ec;
    if (!fs::is_directory(dir_, ec)) return out;

    const std::string active = readActiveStem();

    for (const auto& de : fs::directory_iterator(dir_, ec)) {
        if (!de.is_regular_file() || de.path().extension() != ".json") continue;
        const fs::path jsonPath = de.path();
        fs::path ptPath = jsonPath;
        ptPath.replace_extension(".pt");
        if (!fs::is_regular_file(ptPath, ec)) continue;   // the pair travels together

        std::ifstream in(jsonPath);
        const nlohmann::json j = nlohmann::json::parse(in, nullptr, /*allow_exceptions=*/false);
        if (j.is_discarded() || !j.is_object() || !j.contains("version") || !j["version"].is_string()) {
            NC_LOG_WARN << "skipping unreadable model metadata: " << jsonPath.string();
            continue;
        }

        Found f;
        f.stem = jsonPath.stem().string();
        f.ptPath = ptPath.string();
        ModelEntry& m = f.entry;
        m.version = j["version"].get<std::string>();
        m.id = idFor(m.version);

        // Field names follow ml/Trainer.hpp ModelInfo. epochs_run and best_val_loss are not
        // in that struct yet: they are used when present, otherwise epochs falls back to
        // best_epoch and loss stays unknown.
        const double test = j.value("test_accuracy", 0.0);
        m.accuracy = test > 0 ? test : j.value("val_accuracy", 0.0);
        m.epochs = j.value("epochs_run", j.value("best_epoch", 0));
        m.dataset_size = j.value("dataset_size", 0);
        if (j.contains("best_val_loss") && j["best_val_loss"].is_number()) m.loss = j["best_val_loss"].get<double>();
        m.trained_at = isoFromFileTime(fs::last_write_time(ptPath, ec));
        m.is_active = !active.empty() && f.stem == active;
        out.push_back(std::move(f));
    }

    std::sort(out.begin(), out.end(), [](const Found& a, const Found& b) {
        return a.entry.trained_at != b.entry.trained_at ? a.entry.trained_at < b.entry.trained_at
                                                        : a.entry.version < b.entry.version;
    });
    return out;
}

std::vector<ModelEntry> ModelService::list() const {
    std::lock_guard<std::mutex> lk(mu_);
    std::vector<ModelEntry> out;
    for (auto& f : scan()) out.push_back(std::move(f.entry));
    return out;
}

ModelService::ActivateResult ModelService::activate(std::int64_t id) {
    std::lock_guard<std::mutex> lk(mu_);
    ActivateResult r;

    auto found = scan();
    auto it = std::find_if(found.begin(), found.end(), [&](const Found& f) { return f.entry.id == id; });
    if (it == found.end()) { r.status = ActivateStatus::NotFound; return r; }
    if (!load_) { r.status = ActivateStatus::NotAvailable; return r; }

    if (!load_(it->ptPath)) {
        NC_LOG_ERROR << "model failed to load: " << it->ptPath;
        r.status = ActivateStatus::LoadFailed;
        return r;
    }
    writeActiveStem(it->stem);
    for (auto& f : found) f.entry.is_active = (&f == &*it);
    r.status = ActivateStatus::Ok;
    r.model = it->entry;
    return r;
}

bool ModelService::restoreActive() {
    std::lock_guard<std::mutex> lk(mu_);
    if (!load_) return false;
    const std::string stem = readActiveStem();
    if (stem.empty()) return false;
    for (const auto& f : scan()) {
        if (f.stem == stem) return load_(f.ptPath);
    }
    return false;
}

}  // namespace nc
