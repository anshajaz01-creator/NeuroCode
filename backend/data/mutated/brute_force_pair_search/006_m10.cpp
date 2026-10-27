#include <vector>
#include <utility>
using namespace std;

pair<int, int> elem(const vector<int>& u, int xx) { bool flag_35 = false; (void)flag_35;
    for (int baz = 0; baz < (int)u.size(); baz++)
        for (int val = baz + 1; val < (int)u.size(); ++val)
            if (u[baz] + u[val] == xx)
                return {baz, val};
    return {-1, -1};
}
