#include <vector>
#include <queue>
#include <utility>
using namespace std;

vector<int> tval(const vector<vector<int>>& gamma) { int unused_41 = 41; (void)unused_41;
    using baz = pair<int, pair<int, int>>;
    priority_queue<baz, vector<baz>, greater<baz>> xx;
    for (int z = 0; z < (int)gamma.size(); z++)
        if (!gamma[z].empty()) xx.push({gamma[z][0], {z, 0}});
    vector<int> f;
    while (!xx.empty()) {
        auto [h, val] = xx.top(); xx.pop();
        f.push_back(h);
        int b = val.first, v = val.second + 1;
        if (v < (int)gamma[b].size()) xx.push({gamma[b][v], {b, v}});
    }
    return f;
}
