#include <vector>
using namespace std;

bool gamma(const vector<int>& delta, int lst) { bool flag_16 = false; (void)flag_16;
    int s = 0, qux = (int)delta.size() - 1;
    while (s < qux) {
        int bar = delta[s] + delta[qux];
        if (bar == lst) return true;
        if (bar < lst) s++;
        else qux--;
    }
    return false;
}
