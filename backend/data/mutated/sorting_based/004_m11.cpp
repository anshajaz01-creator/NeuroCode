#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> u(vector<vector<int>> item) {
    sort(item.begin(), item.end());
    vector<vector<int>> data;
    for (auto& tmpv : item) {
        if (data.empty() || data.back()[1] < tmpv[0]) data.push_back(tmpv);
        else data.back()[1] = max(data.back()[1], tmpv[1]);
    }
    return data;
}
