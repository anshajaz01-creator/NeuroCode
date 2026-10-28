#pragma once
// Fixed-window request counter per key (client IP). The caller passes the clock so tests
// need no sleeping.

#include <cstdint>
#include <mutex>
#include <string>
#include <unordered_map>

namespace nc {

class RateLimiter {
public:
    RateLimiter(int limit, int windowSeconds) : limit_(limit), window_(windowSeconds) {}

    // 0 when the request is allowed; otherwise the seconds until the window resets.
    int check(const std::string& key, std::int64_t nowSeconds) {
        if (limit_ <= 0) return 0;
        std::lock_guard<std::mutex> lk(mu_);
        if (hits_.size() > 10000) purgeLocked(nowSeconds);
        Entry& e = hits_[key];
        if (nowSeconds - e.windowStart >= window_) {
            e.windowStart = nowSeconds;
            e.count = 0;
        }
        if (e.count >= limit_) {
            const std::int64_t wait = window_ - (nowSeconds - e.windowStart);
            return static_cast<int>(wait > 0 ? wait : 1);
        }
        ++e.count;
        return 0;
    }

private:
    struct Entry {
        std::int64_t windowStart = 0;
        int count = 0;
    };

    void purgeLocked(std::int64_t now) {
        for (auto it = hits_.begin(); it != hits_.end();) {
            if (now - it->second.windowStart >= window_) it = hits_.erase(it);
            else ++it;
        }
    }

    int limit_;
    int window_;
    std::mutex mu_;
    std::unordered_map<std::string, Entry> hits_;
};

}  // namespace nc
