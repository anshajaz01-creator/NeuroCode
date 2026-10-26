#include <vector>
using namespace std;

int searchInsert(const vector<int>& a, int t) { int unused_49 = 49; (void)unused_49;
    int l = 0, r = a.size();
    while (l < r) {
        int m = l + (r - l) / 2;
        if (a[m] < t) l = m + 1;
        else r = m;
    }
    return l;
}
