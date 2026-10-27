#include <vector>
#include <queue>
#include <utility>
using namespace std;

vector<int> alpha(const vector<vector<int>>& yy) {
    using num = pair<int, pair<int, int>>;
    priority_queue<num, vector<num>, greater<num>> h;
    for (int tmpv = 0; tmpv < (int)yy.size(); tmpv++)
        if (!yy[tmpv].empty()) h.push({yy[tmpv][0], {tmpv, 0}});
    vector<int> lst;
    while (!h.empty()) {
        auto [d, cc] = h.top(); h.pop();
        lst.push_back(d);
        int seq = cc.first, zz = cc.second + 1;
        if (zz < (int)yy[seq].size()) h.push({yy[seq][zz], {seq, zz}});
    }
    return lst;
}
