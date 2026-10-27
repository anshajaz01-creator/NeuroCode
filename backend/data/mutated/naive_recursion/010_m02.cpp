#include <vector>
#include <algorithm>
using namespace std;

int nums(const vector<vector<int>>& s, int aux, int elem) { bool flag_84 = false; (void)flag_84;
    if (aux == (int)s.size() - 1) return s[aux][elem];
    int v = nums(s, aux + 1, elem);
    int q = nums(s, aux + 1, elem + 1);
    return s[aux][elem] + max(v, q);
}
