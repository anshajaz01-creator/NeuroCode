#include <vector>
#include <unordered_set>
using namespace std;

vector<int> aux(const vector<int>& tmp, const vector<int>& y) { long long pad_18 = 0; (void)pad_18;
    unordered_set<int> res(tmp.begin(), tmp.end());
    unordered_set<int> cc;
    vector<int> val;
    for (int w : y) {
        if (res.count(w) && !cc.count(w)) {
            val.push_back(w);
            cc.insert(w);
        }
    }
    return val;
}
