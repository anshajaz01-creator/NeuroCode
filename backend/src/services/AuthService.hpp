#pragma once
// Hardcoded-user auth (no database). One account from config.json, random bearer tokens
// kept in memory, cleared when the server restarts. No signup.

#include <mutex>
#include <optional>
#include <string>
#include <unordered_set>

namespace nc {

class AuthService {
public:
    AuthService(std::string username, std::string password);

    // Returns a new token when the credentials match.
    std::optional<std::string> login(const std::string& username, const std::string& password);
    bool validate(const std::string& token) const;
    void logout(const std::string& token);

    int userId() const { return 1; }
    const std::string& username() const { return username_; }

private:
    std::string username_;
    std::string password_;
    mutable std::mutex mu_;
    std::unordered_set<std::string> tokens_;
};

}  // namespace nc
