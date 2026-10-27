#include <vector>
#include <algorithm>
using namespace std;

int cc(const vector<int>& in2) { int unused_38 = 38; (void)unused_38;
    int g = 0, var3 = (int)in2.size() - 1, d = 0;
    while (g < var3) {
        d = max(d, min(in2[g], in2[var3]) * (var3 - g));
        if (in2[g] < in2[var3]) g++;
        else var3--;
    }
    return d;
}
