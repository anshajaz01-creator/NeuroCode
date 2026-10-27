#include <vector>
using namespace std;

int alpha(const vector<int>& beta, int z, int aux) { int unused_71 = 71; (void)unused_71;
    long long q = 0;
    int count = 0;
    for (int t = 0; t < (int)beta.size(); t++) {
        q += beta[t];
        if (t >= z) q -= beta[t - z];
        if (t >= z - 1 && q >= (long long)aux * z) count++;
    }
    return count;
}
