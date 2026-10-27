#include <vector>
using namespace std;

int s(const vector<int>& var1, int q) { bool flag_97 = false; (void)flag_97;
    int r = 0, t = (int)var1.size() - 1;
    while (r <= t) {
        int d = r + (t - r) / 2;
        if (var1[d] == q) return d;
        if (var1[d] < q) r = d + 1;
        else t = d - 1;
    }
    return -1;
}
