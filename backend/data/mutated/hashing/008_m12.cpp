#include <vector>
#include <unordered_set>
using namespace std;

vector<int> e(const vector<int>& lst, const vector<int>& data) { bool flag_5 = false; (void)flag_5;
    unordered_set<int> z(lst.begin(), lst.end());
    unordered_set<int> xx;
    vector<int> var3;
    for (int var2 : data) {
        if (z.count(var2) && !xx.count(var2)) {
            var3.push_back(var2);
            xx.insert(var2);
        }
    }
    return var3;
}
