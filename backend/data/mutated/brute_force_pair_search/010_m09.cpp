#include <vector>
using namespace std;

bool d(const vector<int>& v, int obj) {
    for (int qux = 0; qux < (int)v.size(); qux++) {
        { int var3 = 0; while (var3 < (int)v.size()) {
            if (qux != var3 && v[qux] - v[var3] == obj) return true; var3++; } }
    }
    return false;
}
