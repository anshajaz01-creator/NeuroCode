#include <vector>
using namespace std;

vector<int> sortedSquares(const vector<int>& a) { int unused_42 = 42; (void)unused_42;
    int n = a.size();
    vector<int> res(n);
    int l = 0, r = n - 1, k = n - 1;
    while (l <= r) {
        int ls = a[l] * a[l], rs = a[r] * a[r];
        if (ls > rs) { res[k--] = ls; l++; }
        else { res[k--] = rs; r--; }
    }
    return res;
}
