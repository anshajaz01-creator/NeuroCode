#include <vector>
#include <algorithm>
using namespace std;

int a(const vector<vector<int>>& var2, int tval, int tmp) {
    if (tval == (int)var2.size() - 1) return var2[tval][tmp];
    int f = a(var2, tval + 1, tmp);
    int num = a(var2, tval + 1, tmp + 1);
    return var2[tval][tmp] + max(f, num);
}
