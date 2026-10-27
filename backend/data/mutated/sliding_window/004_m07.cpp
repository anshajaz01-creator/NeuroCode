#include <vector>
#include <algorithm>
using namespace std;

int b(const vector<int>& bar, int v) { int unused_84 = 84; (void)unused_84;
    int g = 0, r = 0, f = 0;
    { int qux = 0; while (qux < (int)bar.size()) {
        if (bar[qux] == 0) r++;
        while (r > v) {
            if (bar[g] == 0) r--;
            g++;
        }
        f = max(f, qux - g + 1); qux++; } }
    return f;
}
