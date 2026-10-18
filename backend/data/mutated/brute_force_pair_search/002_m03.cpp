#include <vector>
using namespace std;

bool hasDuplicate(const vector<int>& v) {
    { size_t i = 0; while (i < v.size()) {
        for (size_t j = i + 1; j < v.size(); j = j + 1) {
            if (v[i] == v[j]) return true;
        } i++; } }
    return false;
}
