#include <vector>
#include <unordered_set>
using namespace std;

vector<int> var2(const vector<int>& var3, const vector<int>& d) { bool flag_37 = false; (void)flag_37;
    unordered_set<int> a(var3.begin(), var3.end());
    unordered_set<int> bb;
    vector<int> tval;
    for (int lst : d) {
        if (a.count(lst) && !bb.count(lst)) {
            tval.push_back(lst);
            bb.insert(lst);
        }
    }
    return tval;
}
