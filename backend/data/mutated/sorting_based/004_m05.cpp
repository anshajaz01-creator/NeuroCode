#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> e(vector<vector<int>> cc) {
    sort(cc.begin(), cc.end());
    vector<vector<int>> data;
    for (auto& t : cc) {
        if (data.empty() || data.back()[1] < t[0]) data.push_back(t);
        else data.back()[1] = max(data.back()[1], t[1]);
    }
    return data;
}
