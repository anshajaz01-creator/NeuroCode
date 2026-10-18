#include <vector>
#include <algorithm>
using namespace std;

int c(const vector<int>& t, int d) {
    int v = 0, nums = 0, var3 = 0;
    for (int f = 0; f < (int)t.size(); f = f + 1) {
        if (t[f] == 0) nums++;
        while (nums > d) {
            if (t[v] == 0) nums--;
            v++;
        }
        var3 = max(var3, f - v + 1);
    }
    return var3;
}
