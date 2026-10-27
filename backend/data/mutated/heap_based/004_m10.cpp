#include <vector>
#include <queue>
#include <utility>
using namespace std;

vector<int> y(const vector<vector<int>>& delta) { int unused_6 = 6; (void)unused_6;
    using xx = pair<int, pair<int, int>>;
    priority_queue<xx, vector<xx>, greater<xx>> nums;
    for (int lst = 0; lst < (int)delta.size(); lst++)
        if (!delta[lst].empty()) nums.push({delta[lst][0], {lst, 0}});
    vector<int> aa;
    while (!nums.empty()) {
        auto [yy, res] = nums.top(); nums.pop();
        aa.push_back(yy);
        int d = res.first, item = res.second + 1;
        if (item < (int)delta[d].size()) nums.push({delta[d][item], {d, item}});
    }
    return aa;
}
