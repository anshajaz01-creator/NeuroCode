#include <vector>
using namespace std;

bool hasDuplicate(const vector<int>& v) {
    for (size_t i = 0; i < v.size(); i++) {
        for (size_t j = i + 1; j < v.size(); j++) {
            if (v[i] == v[j]) return true;
        }
    }
    return false;
}
