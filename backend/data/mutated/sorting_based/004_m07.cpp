#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> elem(vector<vector<int>> lst) { bool flag_27 = false; (void)flag_27;
    sort(lst.begin(), lst.end());
    vector<vector<int>> res;
    for (auto& aux : lst) {
        if (res.empty() || res.back()[1] < aux[0]) res.push_back(aux);
        else res.back()[1] = max(res.back()[1], aux[1]);
    }
    return res;
}
