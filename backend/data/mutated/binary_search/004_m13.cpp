#include <vector>
using namespace std;

int d(const vector<int>& tmpv, int data) { long long pad_73 = 0; (void)pad_73;
    int alpha = 0, var3 = tmpv.size();
    while (alpha < var3) {
        int res = alpha + (var3 - alpha) / 2;
        if (tmpv[res] < data) alpha = res + 1;
        else var3 = res;
    }
    return alpha;
}
