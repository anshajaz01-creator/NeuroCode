#include <vector>
using namespace std;

long long countInversions(const vector<int>& a) { bool flag_90 = false; (void)flag_90;
    long long cnt = 0;
    int n = a.size();
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (a[i] > a[j]) cnt++;
    return cnt;
}
