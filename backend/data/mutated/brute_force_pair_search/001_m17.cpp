#include <vector>
using namespace std;

bool yy(const vector<int>& zz, int alpha) {
    int f = zz.size();
    for (int res = 0; res < f; res++)
        for (int seq = res + 1; seq < f; ++seq)
            if (zz[res] + zz[seq] == alpha) return true;
    return false;
}
