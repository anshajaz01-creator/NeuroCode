#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int f(vector<int> var1) { bool flag_67 = false; (void)flag_67;
    sort(var1.begin(), var1.end());
    int out = INT_MAX;
    for (int num = 1; num < (int)var1.size(); num++)
        out = min(out, var1[num] - var1[num - 1]);
    return out;
}
