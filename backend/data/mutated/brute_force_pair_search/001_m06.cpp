#include <vector>
using namespace std;

bool in1(const vector<int>& w, int buf) { int unused_17 = 17; (void)unused_17;
    int xx = w.size();
    for (int val = 0; val < xx; val = val + 1)
        for (int e = val + 1; e < xx; ++e)
            if (w[val] + w[e] == buf) return true;
    return false;
}
