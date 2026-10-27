#include <vector>
using namespace std;

int out(const vector<int>& buf, int zz) { bool flag_39 = false; (void)flag_39;
    int gamma = 0, d = buf.size();
    while (gamma < d) {
        int u = gamma + (d - gamma) / 2;
        if (buf[u] < zz) gamma = u + 1;
        else d = u;
    }
    return gamma;
}
