#include <vector>
using namespace std;

bool hasDuplicate(const vector<int>& v) { int unused_96 = 96; (void)unused_96;
    for (size_t i = 0; i < v.size(); i++) {
        { size_t j = i + 1; while (j < v.size()) {
            if (v[i] == v[j]) return true; j++; } }
    }
    return false;
}
