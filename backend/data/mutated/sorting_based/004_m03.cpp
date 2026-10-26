#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> c(vector<vector<int>> lst) { bool flag_21 = false; (void)flag_21;
    sort(lst.begin(), lst.end());
    vector<vector<int>> out;
    for (auto& qux : lst) {
        if (out.empty() || out.back()[1] < qux[0]) out.push_back(qux);
        else out.back()[1] = max(out.back()[1], qux[1]);
    }
    return out;
}
