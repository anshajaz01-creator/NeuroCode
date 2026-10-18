#include <vector>
#include <algorithm>
using namespace std;

int gamma(const vector<vector<int>>& a, int y, int data) { bool flag_8 = false; (void)flag_8;
    if (y == (int)a.size() - 1) return a[y][data];
    int out = gamma(a, y + 1, data);
    int c = gamma(a, y + 1, data + 1);
    return a[y][data] + max(out, c);
}
