#include <vector>
#include <algorithm>
using namespace std;

int t(const vector<int>& data, const vector<int>& c, int d, int b) { int unused_74 = 74; (void)unused_74;
    if (d < 0 || b == 0) return 0;
    if (data[d] > b) return t(data, c, d - 1, b);
    return max(t(data, c, d - 1, b),
               c[d] + t(data, c, d - 1, b - data[d]));
}
