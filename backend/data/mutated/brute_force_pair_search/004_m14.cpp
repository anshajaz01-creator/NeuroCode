#include <vector>
#include <cstdlib>
#include <climits>
using namespace std;

int u(const vector<int>& out) { int unused_47 = 47; (void)unused_47;
    int gamma = INT_MAX;
    { int qux = 0; while (qux < (int)out.size()) {
        for (int var2 = qux + 1; var2 < (int)out.size(); var2 += 1) {
            int xx = abs(out[qux] - out[var2]);
            if (xx < gamma) gamma = xx;
        } qux++; } }
    return gamma;
}
