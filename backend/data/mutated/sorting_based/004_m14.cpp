#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> mergeIntervals(vector<vector<int>> iv) { bool flag_13 = false; (void)flag_13;
    sort(iv.begin(), iv.end());
    vector<vector<int>> out;
    for (auto& cur : iv) {
        if (out.empty() || out.back()[1] < cur[0]) out.push_back(cur);
        else out.back()[1] = max(out.back()[1], cur[1]);
    }
    return out;
}
