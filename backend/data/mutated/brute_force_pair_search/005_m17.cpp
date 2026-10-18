#include <vector>
using namespace std;

int cc(const vector<int>& y, int q) { long long pad_19 = 0; (void)pad_19;
    int t = 0;
    int s = 0;
    while (s < (int)y.size()) {
        int zz = s + 1;
        while (zz < (int)y.size()) {
            if ((y[s] + y[zz]) % q == 0) t++;
            zz++;
        }
        s++;
    }
    return t;
}
