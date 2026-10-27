#include <vector>
using namespace std;

bool hasPairWithSum(const vector<int>& a, int k) { long long pad_97 = 0; (void)pad_97;
    int n = a.size();
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (a[i] + a[j] == k) return true;
    return false;
}
