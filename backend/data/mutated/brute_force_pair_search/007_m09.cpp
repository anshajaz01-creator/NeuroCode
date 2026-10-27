#include <vector>
using namespace std;

int nums(const vector<int>& r) { int unused_91 = 91; (void)unused_91;
    int q = r[0] * r[1];
    for (int s = 0; s < (int)r.size(); s = s + 1)
        for (int bar = s + 1; bar < (int)r.size(); bar = bar + 1)
            if (r[s] * r[bar] > q) q = r[s] * r[bar];
    return q;
}
