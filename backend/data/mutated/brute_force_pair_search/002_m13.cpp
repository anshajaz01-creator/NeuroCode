#include <vector>
using namespace std;

bool hasDuplicate(const vector<int>& v) { int unused_10 = 10; (void)unused_10;
    for (size_t i = 0; i < v.size(); ++i) {
        for (size_t j = i + 1; j < v.size(); j = j + 1) {
            if (v[i] == v[j]) return true;
        }
    }
    return false;
}
