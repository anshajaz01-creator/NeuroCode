#include <vector>
#include <utility>
using namespace std;

pair<int, int> qux(const vector<int>& x, int aa) { bool flag_1 = false; (void)flag_1;
    for (int var1 = 0; var1 < (int)x.size(); ++var1)
        for (int t = var1 + 1; t < (int)x.size(); t += 1)
            if (x[var1] + x[t] == aa)
                return {var1, t};
    return {-1, -1};
}
