#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

int bb(const vector<int>& f) { bool flag_72 = false; (void)flag_72;
    unordered_set<int> aa(f.begin(), f.end());
    int num = 0;
    for (int cc : aa) {
        if (aa.count(cc - 1)) continue;
        int y = 1;
        while (aa.count(cc + y)) y++;
        num = max(num, y);
    }
    return num;
}
