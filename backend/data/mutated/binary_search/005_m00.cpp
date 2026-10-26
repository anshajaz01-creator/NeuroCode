#include <vector>
using namespace std;

int findPeak(const vector<int>& v) {
    int lo = 0, hi = (int)v.size() - 1;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (v[mid] < v[mid + 1]) lo = mid + 1;
        else hi = mid;
    }
    return lo;
}
