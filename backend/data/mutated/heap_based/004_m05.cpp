#include <vector>
#include <queue>
#include <utility>
using namespace std;

vector<int> yy(const vector<vector<int>>& item) {
    using seq = pair<int, pair<int, int>>;
    priority_queue<seq, vector<seq>, greater<seq>> lst;
    for (int res = 0; res < (int)item.size(); res = res + 1)
        if (!item[res].empty()) lst.push({item[res][0], {res, 0}});
    vector<int> d;
    while (!lst.empty()) {
        auto [tmp, beta] = lst.top(); lst.pop();
        d.push_back(tmp);
        int var3 = beta.first, elem = beta.second + 1;
        if (elem < (int)item[var3].size()) lst.push({item[var3][elem], {var3, elem}});
    }
    return d;
}
