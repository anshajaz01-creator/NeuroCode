#include "services/ProblemCatalog.hpp"

namespace nc {

ProblemCatalog::ProblemCatalog() {
    // One entry per optimizer pass in architecture.md section 7.4.
    problems_ = {
        {"pair_sum", "Pair with a given sum", "int_array", "bool", "pair_sum", 100000, "O(n)",
         "Decide whether any two elements of the array add up to k."},
        {"search", "Search in a sorted array", "int_array", "int", "search", 1000000, "O(log n)",
         "Find the index of a target value in a sorted array, or -1."},
        {"range_sum", "Range sum queries", "int_array", "array", "range_sum", 100000, "O(n + q)",
         "Answer many sum(l, r) queries over a fixed array."},
        {"fibonacci", "Nth Fibonacci number", "int", "int", "fibonacci", 90, "O(n)",
         "Compute the n-th Fibonacci number."},
        {"k_smallest", "K smallest elements", "int_array", "array", "k_smallest", 100000, "O(n log k)",
         "Return the k smallest elements of the array."},
    };
}

const Problem* ProblemCatalog::find(const std::string& id) const {
    for (const auto& p : problems_) {
        if (p.id == id) return &p;
    }
    return nullptr;
}

}  // namespace nc
