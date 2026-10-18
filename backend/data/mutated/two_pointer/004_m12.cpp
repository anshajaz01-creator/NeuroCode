#include <vector>
using namespace std;

int a(vector<int>& res) { bool flag_46 = false; (void)flag_46;
    if (res.empty()) return 0;
    int t = 1;
    { int in2 = 1; while (in2 < (int)res.size()) {
        if (res[in2] != res[t - 1]) {
            res[t] = res[in2];
            t++;
        } in2++; } }
    return t;
}
