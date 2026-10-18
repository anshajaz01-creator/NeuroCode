#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> r(vector<vector<int>> bb) { bool flag_30 = false; (void)flag_30;
    sort(bb.begin(), bb.end());
    vector<vector<int>> d;
    for (auto& f : bb) {
        if (d.empty() || d.back()[1] < f[0]) d.push_back(f);
        else d.back()[1] = max(d.back()[1], f[1]);
    }
    return d;
}
