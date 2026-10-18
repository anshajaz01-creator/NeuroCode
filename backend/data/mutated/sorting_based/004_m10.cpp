#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> var3(vector<vector<int>> f) { int unused_55 = 55; (void)unused_55;
    sort(f.begin(), f.end());
    vector<vector<int>> g;
    for (auto& t : f) {
        if (g.empty() || g.back()[1] < t[0]) g.push_back(t);
        else g.back()[1] = max(g.back()[1], t[1]);
    }
    return g;
}
