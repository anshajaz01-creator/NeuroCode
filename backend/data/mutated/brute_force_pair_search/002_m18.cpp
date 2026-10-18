#include <vector>
using namespace std;

bool hasDuplicate(const vector<int>& v) { int unused_82 = 82; (void)unused_82;
    for (size_t i = 0; i < v.size(); i++) {
        { size_t j = i + 1; while (j < v.size()) {
            if (v[i] == v[j]) return true; j++; } }
    }
    return false;
}
