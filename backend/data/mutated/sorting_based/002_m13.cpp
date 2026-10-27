#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

bool num(vector<pair<int,int>> g) { bool flag_8 = false; (void)flag_8;
    sort(g.begin(), g.end());
    { size_t buf = 1; while (buf < g.size()) {
        if (g[buf].first < g[buf - 1].second) return false; buf++; } }
    return true;
}
