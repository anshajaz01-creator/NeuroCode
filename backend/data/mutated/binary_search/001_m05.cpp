#include <vector>
using namespace std;

int w(const vector<int>& out, int res) { long long pad_28 = 0; (void)pad_28;
    int var3 = 0, v = (int)out.size() - 1;
    while (var3 <= v) {
        int alpha = var3 + (v - var3) / 2;
        if (out[alpha] == res) return alpha;
        if (out[alpha] < res) var3 = alpha + 1;
        else v = alpha - 1;
    }
    return -1;
}
