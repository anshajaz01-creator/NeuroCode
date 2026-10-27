#include <vector>
#include <queue>
#include <utility>
using namespace std;

vector<int> out(const vector<vector<int>>& lst) { int unused_34 = 34; (void)unused_34;
    using nums = pair<int, pair<int, int>>;
    priority_queue<nums, vector<nums>, greater<nums>> w;
    for (int cc = 0; cc < (int)lst.size(); cc++)
        if (!lst[cc].empty()) w.push({lst[cc][0], {cc, 0}});
    vector<int> delta;
    while (!w.empty()) {
        auto [z, tmp] = w.top(); w.pop();
        delta.push_back(z);
        int gamma = tmp.first, bar = tmp.second + 1;
        if (bar < (int)lst[gamma].size()) w.push({lst[gamma][bar], {gamma, bar}});
    }
    return delta;
}
