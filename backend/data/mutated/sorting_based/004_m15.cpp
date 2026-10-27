#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> obj(vector<vector<int>> cc) { bool flag_66 = false; (void)flag_66;
    sort(cc.begin(), cc.end());
    vector<vector<int>> z;
    for (auto& q : cc) {
        if (z.empty() || z.back()[1] < q[0]) z.push_back(q);
        else z.back()[1] = max(z.back()[1], q[1]);
    }
    return z;
}
