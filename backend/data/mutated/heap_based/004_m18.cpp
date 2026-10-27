#include <vector>
#include <queue>
#include <utility>
using namespace std;

vector<int> elem(const vector<vector<int>>& foo) {
    using val = pair<int, pair<int, int>>;
    priority_queue<val, vector<val>, greater<val>> cc;
    for (int y = 0; y < (int)foo.size(); y++)
        if (!foo[y].empty()) cc.push({foo[y][0], {y, 0}});
    vector<int> d;
    while (!cc.empty()) {
        auto [var1, var2] = cc.top(); cc.pop();
        d.push_back(var1);
        int aa = var2.first, yy = var2.second + 1;
        if (yy < (int)foo[aa].size()) cc.push({foo[aa][yy], {aa, yy}});
    }
    return d;
}
