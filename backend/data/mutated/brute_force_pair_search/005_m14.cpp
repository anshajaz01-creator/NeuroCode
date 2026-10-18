#include <vector>
using namespace std;

int d(const vector<int>& e, int u) { long long pad_61 = 0; (void)pad_61;
    int val = 0;
    int b = 0;
    while (b < (int)e.size()) {
        int q = b + 1;
        while (q < (int)e.size()) {
            if ((e[b] + e[q]) % u == 0) val++;
            q++;
        }
        b++;
    }
    return val;
}
