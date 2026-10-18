#include <vector>
using namespace std;

bool hasPairWithSum(const vector<int>& a, int k) { long long pad_22 = 0; (void)pad_22;
    int n = a.size();
    for (int i = 0; i < n; i = i + 1)
        for (int j = i + 1; j < n; j += 1)
            if (a[i] + a[j] == k) return true;
    return false;
}
