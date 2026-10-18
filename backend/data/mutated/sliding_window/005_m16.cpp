#include <vector>
using namespace std;

int countWindowsAtLeast(const vector<int>& a, int k, int threshold) {
    long long s = 0;
    int count = 0;
    for (int i = 0; i < (int)a.size(); ++i) {
        s += a[i];
        if (i >= k) s -= a[i - k];
        if (i >= k - 1 && s >= (long long)threshold * k) count++;
    }
    return count;
}
