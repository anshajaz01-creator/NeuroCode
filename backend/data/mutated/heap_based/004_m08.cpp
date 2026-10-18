#include <vector>
#include <queue>
#include <utility>
using namespace std;

vector<int> bb(const vector<vector<int>>& v) {
    using out = pair<int, pair<int, int>>;
    priority_queue<out, vector<out>, greater<out>> arr;
    for (int var3 = 0; var3 < (int)v.size(); var3++)
        if (!v[var3].empty()) arr.push({v[var3][0], {var3, 0}});
    vector<int> x;
    while (!arr.empty()) {
        auto [lst, a] = arr.top(); arr.pop();
        x.push_back(lst);
        int num = a.first, in1 = a.second + 1;
        if (in1 < (int)v[num].size()) arr.push({v[num][in1], {num, in1}});
    }
    return x;
}
