#include <vector>
using namespace std;

int f(const vector<int>& tmpv, int t, int e) {
    if (e == 0) return 1;
    if (e < 0 || t == 0) return 0;
    return f(tmpv, t, e - tmpv[t - 1]) + f(tmpv, t - 1, e);
}
