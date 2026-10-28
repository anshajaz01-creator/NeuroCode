#pragma once
// In-code problem catalog. Replaces the seeded `problems` table (no database).
// reference_code (the oracle solutions from architecture.md section 6) is NOT here: it is
// T4's Oracle input, not something the API serves.

#include <string>
#include <vector>

namespace nc {

struct Problem {
    std::string id;
    std::string title;
    std::string input_type;
    std::string output_type;
    std::string operation;
    long long max_n = 0;
    std::string optimal_time;
    std::string description;
};

class ProblemCatalog {
public:
    ProblemCatalog();
    const std::vector<Problem>& all() const { return problems_; }
    const Problem* find(const std::string& id) const;

private:
    std::vector<Problem> problems_;
};

}  // namespace nc
