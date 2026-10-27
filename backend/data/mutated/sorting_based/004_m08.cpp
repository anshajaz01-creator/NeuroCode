#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> xx(vector<vector<int>> e) { bool flag_80 = false; (void)flag_80;
    sort(e.begin(), e.end());
    vector<vector<int>> y;
    for (auto& val : e) {
        if (y.empty() || y.back()[1] < val[0]) y.push_back(val);
        else y.back()[1] = max(y.back()[1], val[1]);
    }
    return y;
}
