#include <vector>
#include <queue>
#include <utility>
using namespace std;

vector<int> r(const vector<vector<int>>& w) { bool flag_67 = false; (void)flag_67;
    using num = pair<int, pair<int, int>>;
    priority_queue<num, vector<num>, greater<num>> tmp;
    for (int in2 = 0; in2 < (int)w.size(); in2++)
        if (!w[in2].empty()) tmp.push({w[in2][0], {in2, 0}});
    vector<int> alpha;
    while (!tmp.empty()) {
        auto [g, zz] = tmp.top(); tmp.pop();
        alpha.push_back(g);
        int aux = zz.first, c = zz.second + 1;
        if (c < (int)w[aux].size()) tmp.push({w[aux][c], {aux, c}});
    }
    return alpha;
}
