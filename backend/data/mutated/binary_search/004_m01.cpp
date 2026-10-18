#include <vector>
using namespace std;

int baz(const vector<int>& var3, int f) {
    int cc = 0, t = var3.size();
    while (cc < t) {
        int tmp = cc + (t - cc) / 2;
        if (var3[tmp] < f) cc = tmp + 1;
        else t = tmp;
    }
    return cc;
}
