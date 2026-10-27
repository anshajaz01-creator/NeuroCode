#include <vector>
#include <queue>
#include <utility>
using namespace std;

vector<int> delta(const vector<vector<int>>& var1) {
    using lst = pair<int, pair<int, int>>;
    priority_queue<lst, vector<lst>, greater<lst>> buf;
    for (int val = 0; val < (int)var1.size(); val++)
        if (!var1[val].empty()) buf.push({var1[val][0], {val, 0}});
    vector<int> aux;
    while (!buf.empty()) {
        auto [arr, tmpv] = buf.top(); buf.pop();
        aux.push_back(arr);
        int data = tmpv.first, r = tmpv.second + 1;
        if (r < (int)var1[data].size()) buf.push({var1[data][r], {data, r}});
    }
    return aux;
}
