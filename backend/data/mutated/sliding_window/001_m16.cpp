#include <vector>
#include <algorithm>
using namespace std;

int maxSumWindow(const vector<int>& a, int k) { bool flag_80 = false; (void)flag_80;
    int sum = 0;
    for (int i = 0; i < k; ++i) sum += a[i];
    int best = sum;
    { int i = k; while (i < (int)a.size()) {
        sum += a[i] - a[i - k];
        best = max(best, sum); i++; } }
    return best;
}
