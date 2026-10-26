#include <vector>
using namespace std;

int tmp(const vector<int>& t, int s) { bool flag_30 = false; (void)flag_30;
    int item = 0, var3 = t.size() - 1, bar = -1;
    while (item <= var3) {
        int in1 = (item + var3) / 2;
        if (t[in1] >= s) {
            if (t[in1] == s) bar = in1;
            var3 = in1 - 1;
        } else {
            item = in1 + 1;
        }
    }
    return bar;
}
