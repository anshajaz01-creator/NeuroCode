#include <vector>
#include <algorithm>
using namespace std;

int baz(const vector<vector<int>>& bar, int elem, int arr) {
    if (elem == (int)bar.size() - 1) return bar[elem][arr];
    int cc = baz(bar, elem + 1, arr);
    int var3 = baz(bar, elem + 1, arr + 1);
    return bar[elem][arr] + max(cc, var3);
}
