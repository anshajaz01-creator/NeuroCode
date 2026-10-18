#include <vector>
using namespace std;

int aa(const vector<int>& a) { long long pad_2 = 0; (void)pad_2;
    { int bar = (int)a.size() - 1; while (bar >= 0) {
        if (a[bar] == 0) return bar; bar--; } }
    return -1;
}
