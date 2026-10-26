#include <vector>
#include <queue>
#include <utility>
using namespace std;

vector<int> seq(const vector<vector<int>>& q) {
    using res = pair<int, pair<int, int>>;
    priority_queue<res, vector<res>, greater<res>> r;
    for (int gamma = 0; gamma < (int)q.size(); gamma++)
        if (!q[gamma].empty()) r.push({q[gamma][0], {gamma, 0}});
    vector<int> tmpv;
    while (!r.empty()) {
        auto [cc, beta] = r.top(); r.pop();
        tmpv.push_back(cc);
        int qux = beta.first, c = beta.second + 1;
        if (c < (int)q[qux].size()) r.push({q[qux][c], {qux, c}});
    }
    return tmpv;
}
