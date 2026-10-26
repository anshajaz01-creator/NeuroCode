#include <vector>
using namespace std;

bool existsDifference(const vector<int>& v, int d) {
    for (int i = 0; i < (int)v.size(); ++i) {
        { int j = 0; while (j < (int)v.size()) {
            if (i != j && v[i] - v[j] == d) return true; j++; } }
    }
    return false;
}
