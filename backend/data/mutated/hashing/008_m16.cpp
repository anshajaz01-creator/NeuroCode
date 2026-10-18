#include <vector>
#include <unordered_set>
using namespace std;

vector<int> tval(const vector<int>& d, const vector<int>& g) { bool flag_80 = false; (void)flag_80;
    unordered_set<int> foo(d.begin(), d.end());
    unordered_set<int> bb;
    vector<int> var1;
    for (int item : g) {
        if (foo.count(item) && !bb.count(item)) {
            var1.push_back(item);
            bb.insert(item);
        }
    }
    return var1;
}
