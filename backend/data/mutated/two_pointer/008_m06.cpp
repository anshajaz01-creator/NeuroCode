#include <vector>
using namespace std;

vector<int> seq(const vector<int>& t) {
    int r = t.size();
    vector<int> tmpv(r);
    int s = 0, q = r - 1, gamma = r - 1;
    while (s <= q) {
        int u = t[s] * t[s], x = t[q] * t[q];
        if (u > x) { tmpv[gamma--] = u; s++; }
        else { tmpv[gamma--] = x; q--; }
    }
    return tmpv;
}
