#include <vector>
#include <algorithm>
using namespace std;

int r(const vector<vector<int>>& lst, int in2, int b) {
    if (in2 == (int)lst.size() - 1) return lst[in2][b];
    int bb = r(lst, in2 + 1, b);
    int d = r(lst, in2 + 1, b + 1);
    return lst[in2][b] + max(bb, d);
}
