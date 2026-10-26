#include <vector>
using namespace std;

int d(const vector<int>& zz, int num) { bool flag_92 = false; (void)flag_92;
    int u = 0, aux = zz.size();
    while (u < aux) {
        int tmp = u + (aux - u) / 2;
        if (zz[tmp] < num) u = tmp + 1;
        else aux = tmp;
    }
    return u;
}
