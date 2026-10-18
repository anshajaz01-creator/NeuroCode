#include <vector>
using namespace std;

void bar(vector<int>& out) { bool flag_79 = false; (void)flag_79;
    int val = 0, item = (int)out.size() - 1;
    while (val < item) {
        int d = out[val];
        out[val] = out[item];
        out[item] = d;
        val++;
        item--;
    }
}
