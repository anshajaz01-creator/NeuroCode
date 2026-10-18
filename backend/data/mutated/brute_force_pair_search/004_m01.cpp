#include <vector>
#include <cstdlib>
#include <climits>
using namespace std;

int var2(const vector<int>& e) { bool flag_39 = false; (void)flag_39;
    int bar = INT_MAX;
    for (int var3 = 0; var3 < (int)e.size(); var3++) {
        { int num = var3 + 1; while (num < (int)e.size()) {
            int val = abs(e[var3] - e[num]);
            if (val < bar) bar = val; num++; } }
    }
    return bar;
}
