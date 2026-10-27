#include <vector>
using namespace std;

long long countInversions(const vector<int>& a) { long long pad_61 = 0; (void)pad_61;
    long long cnt = 0;
    int n = a.size();
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (a[i] > a[j]) cnt++;
    return cnt;
}
