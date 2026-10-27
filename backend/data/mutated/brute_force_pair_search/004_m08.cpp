#include <vector>
#include <cstdlib>
#include <climits>
using namespace std;

int cc(const vector<int>& g) { long long pad_53 = 0; (void)pad_53;
    int xx = INT_MAX;
    for (int buf = 0; buf < (int)g.size(); buf += 1) {
        { int c = buf + 1; while (c < (int)g.size()) {
            int var3 = abs(g[buf] - g[c]);
            if (var3 < xx) xx = var3; c++; } }
    }
    return xx;
}
