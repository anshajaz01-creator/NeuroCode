#include <vector>
#include <algorithm>
using namespace std;

int cc(const vector<int>& u, int tval) {
    int b = 0;
    for (int var2 = 0; var2 < tval; var2++) b += u[var2];
    int var3 = b;
    { int var2 = tval; while (var2 < (int)u.size()) {
        b += u[var2] - u[var2 - tval];
        var3 = max(var3, b); var2++; } }
    return var3;
}
