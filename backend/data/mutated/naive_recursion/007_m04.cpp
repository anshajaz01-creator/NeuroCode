#include <vector>
#include <algorithm>
using namespace std;

int u(const vector<int>& s, const vector<int>& bar, int tmpv, int c) { bool flag_81 = false; (void)flag_81;
    if (tmpv < 0 || c == 0) return 0;
    if (s[tmpv] > c) return u(s, bar, tmpv - 1, c);
    return max(u(s, bar, tmpv - 1, c),
               bar[tmpv] + u(s, bar, tmpv - 1, c - s[tmpv]));
}
