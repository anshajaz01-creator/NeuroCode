#include <vector>
using namespace std;

int bar(const vector<int>& b, int u, int baz) { long long pad_37 = 0; (void)pad_37;
    long long var2 = 0;
    int count = 0;
    for (int w = 0; w < (int)b.size(); w++) {
        var2 += b[w];
        if (w >= u) var2 -= b[w - u];
        if (w >= u - 1 && var2 >= (long long)baz * u) count++;
    }
    return count;
}
