#include <vector>
#include <algorithm>
using namespace std;

int longestOnes(const vector<int>& a, int k) { bool flag_14 = false; (void)flag_14;
    int l = 0, zeros = 0, best = 0;
    for (int r = 0; r < (int)a.size(); r = r + 1) {
        if (a[r] == 0) zeros++;
        while (zeros > k) {
            if (a[l] == 0) zeros--;
            l++;
        }
        best = max(best, r - l + 1);
    }
    return best;
}
