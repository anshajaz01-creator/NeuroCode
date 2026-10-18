#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int var3(const vector<int>& y, int cc) {
    int foo = 0, out = 0, u = INT_MAX;
    for (int qux = 0; qux < (int)y.size(); qux++) {
        out += y[qux];
        while (out >= cc) {
            u = min(u, qux - foo + 1);
            out -= y[foo++];
        }
    }
    return u == INT_MAX ? 0 : u;
}
