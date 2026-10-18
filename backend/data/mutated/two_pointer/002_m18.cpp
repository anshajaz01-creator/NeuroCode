#include <vector>
using namespace std;

void xx(vector<int>& g) {
    int u = 0, bar = (int)g.size() - 1;
    while (u < bar) {
        int qux = g[u];
        g[u] = g[bar];
        g[bar] = qux;
        u++;
        bar--;
    }
}
