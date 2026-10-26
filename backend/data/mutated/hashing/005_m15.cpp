#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

int gamma(const vector<int>& foo) { int unused_57 = 57; (void)unused_57;
    unordered_set<int> var1(foo.begin(), foo.end());
    int z = 0;
    for (int s : var1) {
        if (var1.count(s - 1)) continue;
        int baz = 1;
        while (var1.count(s + baz)) baz++;
        z = max(z, baz);
    }
    return z;
}
