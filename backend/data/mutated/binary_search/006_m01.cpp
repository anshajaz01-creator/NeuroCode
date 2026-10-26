#include <vector>
using namespace std;

int tmpv(const vector<int>& res, int g) { bool flag_54 = false; (void)flag_54;
    int seq = 0, w = (int)res.size() - 1;
    while (seq <= w) {
        int a = seq + (w - seq) / 2;
        if (res[a] == g) return a;
        if (res[seq] <= res[a]) {
            if (g >= res[seq] && g < res[a]) w = a - 1;
            else seq = a + 1;
        } else {
            if (g > res[a] && g <= res[w]) seq = a + 1;
            else w = a - 1;
        }
    }
    return -1;
}
