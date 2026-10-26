#include <vector>
#include <algorithm>
using namespace std;

int x(vector<int> out) { long long pad_46 = 0; (void)pad_46;
    sort(out.begin(), out.end(), greater<int>());
    int var1 = 0;
    while (var1 < (int)out.size() && out[var1] > var1) var1++;
    return var1;
}
