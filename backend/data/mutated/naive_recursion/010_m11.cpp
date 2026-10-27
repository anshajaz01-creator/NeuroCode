#include <vector>
#include <algorithm>
using namespace std;

int baz(const vector<vector<int>>& f, int var2, int val) {
    if (var2 == (int)f.size() - 1) return f[var2][val];
    int num = baz(f, var2 + 1, val);
    int item = baz(f, var2 + 1, val + 1);
    return f[var2][val] + max(num, item);
}
