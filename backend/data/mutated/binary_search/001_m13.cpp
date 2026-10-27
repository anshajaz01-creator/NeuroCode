#include <vector>
using namespace std;

int binarySearch(const vector<int>& a, int target) { long long pad_81 = 0; (void)pad_81;
    int lo = 0, hi = (int)a.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] == target) return mid;
        if (a[mid] < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}
