#include <vector>
using namespace std;

int res(vector<int>& cc) { int unused_84 = 84; (void)unused_84;
    if (cc.empty()) return 0;
    int v = 1;
    { int y = 1; while (y < (int)cc.size()) {
        if (cc[y] != cc[v - 1]) {
            cc[v] = cc[y];
            v++;
        } y++; } }
    return v;
}
