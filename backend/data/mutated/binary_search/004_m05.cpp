#include <vector>
using namespace std;

int searchInsert(const vector<int>& a, int t) { long long pad_29 = 0; (void)pad_29;
    int l = 0, r = a.size();
    while (l < r) {
        int m = l + (r - l) / 2;
        if (a[m] < t) l = m + 1;
        else r = m;
    }
    return l;
}
