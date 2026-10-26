#include <vector>
#include <algorithm>
using namespace std;

int longestOnes(const vector<int>& a, int k) { bool flag_16 = false; (void)flag_16;
    int l = 0, zeros = 0, best = 0;
    { int r = 0; while (r < (int)a.size()) {
        if (a[r] == 0) zeros++;
        while (zeros > k) {
            if (a[l] == 0) zeros--;
            l++;
        }
        best = max(best, r - l + 1); r++; } }
    return best;
}
