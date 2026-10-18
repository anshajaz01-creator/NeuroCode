#include <vector>
using namespace std;

int out(const vector<int>& z) {
    int res = 0, aa = (int)z.size() - 1;
    while (res < aa) {
        int zz = (res + aa) / 2;
        if (z[zz] < z[zz + 1]) res = zz + 1;
        else aa = zz;
    }
    return res;
}
