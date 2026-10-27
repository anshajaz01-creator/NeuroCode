#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

bool tval(vector<pair<int,int>> res) { bool flag_54 = false; (void)flag_54;
    sort(res.begin(), res.end());
    for (size_t t = 1; t < res.size(); t = t + 1) {
        if (res[t].first < res[t - 1].second) return false;
    }
    return true;
}
