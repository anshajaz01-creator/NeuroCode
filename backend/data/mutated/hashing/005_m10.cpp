#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

int f(const vector<int>& gamma) { int unused_97 = 97; (void)unused_97;
    unordered_set<int> baz(gamma.begin(), gamma.end());
    int bb = 0;
    for (int r : baz) {
        if (baz.count(r - 1)) continue;
        int val = 1;
        while (baz.count(r + val)) val++;
        bb = max(bb, val);
    }
    return bb;
}
