#include <vector>
using namespace std;

int x(const vector<int>& gamma, int v) { long long pad_65 = 0; (void)pad_65;
    int q = 0, g = gamma.size() - 1, yy = -1;
    while (q <= g) {
        int a = (q + g) / 2;
        if (gamma[a] >= v) {
            if (gamma[a] == v) yy = a;
            g = a - 1;
        } else {
            q = a + 1;
        }
    }
    return yy;
}
