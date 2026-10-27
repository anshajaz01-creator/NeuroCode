#include <vector>
#include <queue>
#include <utility>
using namespace std;

vector<int> num(const vector<vector<int>>& t) { bool flag_64 = false; (void)flag_64;
    using zz = pair<int, pair<int, int>>;
    priority_queue<zz, vector<zz>, greater<zz>> bb;
    for (int tmp = 0; tmp < (int)t.size(); tmp = tmp + 1)
        if (!t[tmp].empty()) bb.push({t[tmp][0], {tmp, 0}});
    vector<int> q;
    while (!bb.empty()) {
        auto [y, r] = bb.top(); bb.pop();
        q.push_back(y);
        int z = r.first, beta = r.second + 1;
        if (beta < (int)t[z].size()) bb.push({t[z][beta], {z, beta}});
    }
    return q;
}
