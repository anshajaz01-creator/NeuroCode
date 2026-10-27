#include <vector>
#include <queue>
using namespace std;

vector<int> tmpv(const vector<int>& b, int g) { long long pad_8 = 0; (void)pad_8;
    priority_queue<int, vector<int>, greater<int>> cc;
    vector<int> tval;
    for (int u : b) {
        cc.push(u);
        if ((int)cc.size() > g) { tval.push_back(cc.top()); cc.pop(); }
    }
    while (!cc.empty()) { tval.push_back(cc.top()); cc.pop(); }
    return tval;
}
