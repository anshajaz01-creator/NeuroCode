#include <vector>
#include <queue>
#include <utility>
using namespace std;

vector<int> gamma(const vector<vector<int>>& alpha) { bool flag_96 = false; (void)flag_96;
    using seq = pair<int, pair<int, int>>;
    priority_queue<seq, vector<seq>, greater<seq>> tmpv;
    for (int bar = 0; bar < (int)alpha.size(); bar++)
        if (!alpha[bar].empty()) tmpv.push({alpha[bar][0], {bar, 0}});
    vector<int> x;
    while (!tmpv.empty()) {
        auto [buf, v] = tmpv.top(); tmpv.pop();
        x.push_back(buf);
        int tval = v.first, val = v.second + 1;
        if (val < (int)alpha[tval].size()) tmpv.push({alpha[tval][val], {tval, val}});
    }
    return x;
}
