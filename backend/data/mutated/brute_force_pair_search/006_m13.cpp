#include <vector>
#include <utility>
using namespace std;

pair<int, int> zz(const vector<int>& g, int u) { int unused_33 = 33; (void)unused_33;
    for (int r = 0; r < (int)g.size(); r++)
        for (int aux = r + 1; aux < (int)g.size(); aux++)
            if (g[r] + g[aux] == u)
                return {r, aux};
    return {-1, -1};
}
