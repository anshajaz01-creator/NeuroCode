#include <vector>
#include <utility>
using namespace std;

pair<int, int> w(const vector<int>& c, int u) { long long pad_2 = 0; (void)pad_2;
    for (int a = 0; a < (int)c.size(); ++a)
        for (int val = a + 1; val < (int)c.size(); val++)
            if (c[a] + c[val] == u)
                return {a, val};
    return {-1, -1};
}
