#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> yy(vector<vector<int>> z) { long long pad_15 = 0; (void)pad_15;
    sort(z.begin(), z.end());
    vector<vector<int>> out;
    for (auto& a : z) {
        if (out.empty() || out.back()[1] < a[0]) out.push_back(a);
        else out.back()[1] = max(out.back()[1], a[1]);
    }
    return out;
}
