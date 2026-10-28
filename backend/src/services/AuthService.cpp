#include "services/AuthService.hpp"

#include <random>

namespace nc {

namespace {

// Compares without stopping at the first difference.
bool constantTimeEquals(const std::string& a, const std::string& b) {
    unsigned char diff = static_cast<unsigned char>(a.size() ^ b.size());
    const std::size_t n = a.size() < b.size() ? a.size() : b.size();
    for (std::size_t i = 0; i < n; ++i) {
        diff |= static_cast<unsigned char>(a[i] ^ b[i]);
    }
    return diff == 0;
}

std::string randomToken() {
    static const char* hex = "0123456789abcdef";
    std::random_device rd;   // reads the OS entropy source on Linux
    std::string out;
    out.reserve(64);
    for (int i = 0; i < 32; ++i) {
        const unsigned v = rd() & 0xFF;
        out.push_back(hex[v >> 4]);
        out.push_back(hex[v & 0xF]);
    }
    return out;
}

}  // namespace

AuthService::AuthService(std::string username, std::string password)
    : username_(std::move(username)), password_(std::move(password)) {}

std::optional<std::string> AuthService::login(const std::string& username, const std::string& password) {
    // Evaluate both so timing does not reveal which one was wrong.
    const bool userOk = constantTimeEquals(username, username_);
    const bool passOk = constantTimeEquals(password, password_);
    if (!(userOk && passOk)) return std::nullopt;

    std::string token = randomToken();
    std::lock_guard<std::mutex> lk(mu_);
    tokens_.insert(token);
    return token;
}

bool AuthService::validate(const std::string& token) const {
    if (token.empty()) return false;
    std::lock_guard<std::mutex> lk(mu_);
    return tokens_.count(token) > 0;
}

void AuthService::logout(const std::string& token) {
    std::lock_guard<std::mutex> lk(mu_);
    tokens_.erase(token);
}

}  // namespace nc
