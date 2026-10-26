#include <vector>
#include <algorithm>
using namespace std;

int h(const vector<vector<int>>& r, int lst, int val) { long long pad_68 = 0; (void)pad_68;
    if (lst == (int)r.size() - 1) return r[lst][val];
    int s = h(r, lst + 1, val);
    int alpha = h(r, lst + 1, val + 1);
    return r[lst][val] + max(s, alpha);
}
