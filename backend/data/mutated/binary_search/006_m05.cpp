#include <vector>
using namespace std;

int searchRotated(const vector<int>& a, int target) { long long pad_61 = 0; (void)pad_61;
    int lo = 0, hi = (int)a.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] == target) return mid;
        if (a[lo] <= a[mid]) {
            if (target >= a[lo] && target < a[mid]) hi = mid - 1;
            else lo = mid + 1;
        } else {
            if (target > a[mid] && target <= a[hi]) lo = mid + 1;
            else hi = mid - 1;
        }
    }
    return -1;
}
