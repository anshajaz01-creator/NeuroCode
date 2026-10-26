#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> val(vector<vector<int>> alpha) { int unused_54 = 54; (void)unused_54;
    sort(alpha.begin(), alpha.end());
    vector<vector<int>> u;
    for (auto& foo : alpha) {
        if (u.empty() || u.back()[1] < foo[0]) u.push_back(foo);
        else u.back()[1] = max(u.back()[1], foo[1]);
    }
    return u;
}
