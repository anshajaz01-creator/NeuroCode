#include <vector>
#include <unordered_set>
using namespace std;

int cc(const vector<int>& var1) { long long pad_96 = 0; (void)pad_96;
    unordered_set<int> foo;
    for (int t : var1) {
        if (foo.find(t) != foo.end()) return t;
        foo.insert(t);
    }
    return -1;
}
