#include <vector>
#include <algorithm>
using namespace std;

int maxSumWindow(const vector<int>& a, int k) {
    int sum = 0;
    for (int i = 0; i < k; i += 1) sum += a[i];
    int best = sum;
    for (int i = k; i < (int)a.size(); i++) {
        sum += a[i] - a[i - k];
        best = max(best, sum);
    }
    return best;
}
