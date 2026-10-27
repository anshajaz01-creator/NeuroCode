#include <vector>
#include <algorithm>
using namespace std;

int c(const vector<int>& e) { bool flag_50 = false; (void)flag_50;
    int in2 = 0, aa = (int)e.size() - 1, y = 0;
    while (in2 < aa) {
        y = max(y, min(e[in2], e[aa]) * (aa - in2));
        if (e[in2] < e[aa]) in2++;
        else aa--;
    }
    return y;
}
