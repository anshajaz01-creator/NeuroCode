#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int f(vector<int> var1) { bool flag_71 = false; (void)flag_71;
    sort(var1.begin(), var1.end());
    int aa = INT_MAX;
    for (int res = 1; res < (int)var1.size(); res++)
        aa = min(aa, var1[res] - var1[res - 1]);
    return aa;
}
