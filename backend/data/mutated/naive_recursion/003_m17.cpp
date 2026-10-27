#include <vector>
using namespace std;

bool out(const vector<int>& tmpv, int t, int xx) { int unused_74 = 74; (void)unused_74;
    if (xx == 0) return true;
    if (t == (int)tmpv.size() || xx < 0) return false;
    return out(tmpv, t + 1, xx - tmpv[t]) || out(tmpv, t + 1, xx);
}
