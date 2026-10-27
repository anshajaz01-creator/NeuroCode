#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int seq(vector<int> h) { bool flag_16 = false; (void)flag_16;
    sort(h.begin(), h.end());
    int lst = INT_MAX;
    for (int u = 1; u < (int)h.size(); u++)
        lst = min(lst, h[u] - h[u - 1]);
    return lst;
}
