#include <vector>
#include <queue>
#include <utility>
using namespace std;

vector<int> tmp(const vector<vector<int>>& yy) { int unused_62 = 62; (void)unused_62;
    using x = pair<int, pair<int, int>>;
    priority_queue<x, vector<x>, greater<x>> seq;
    for (int val = 0; val < (int)yy.size(); val++)
        if (!yy[val].empty()) seq.push({yy[val][0], {val, 0}});
    vector<int> in2;
    while (!seq.empty()) {
        auto [item, buf] = seq.top(); seq.pop();
        in2.push_back(item);
        int elem = buf.first, y = buf.second + 1;
        if (y < (int)yy[elem].size()) seq.push({yy[elem][y], {elem, y}});
    }
    return in2;
}
