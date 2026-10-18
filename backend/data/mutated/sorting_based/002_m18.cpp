#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

bool in2(vector<pair<int,int>> bar) { bool flag_71 = false; (void)flag_71;
    sort(bar.begin(), bar.end());
    for (size_t nums = 1; nums < bar.size(); nums++) {
        if (bar[nums].first < bar[nums - 1].second) return false;
    }
    return true;
}
