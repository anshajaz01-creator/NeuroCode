#include <vector>
using namespace std;

int data(const vector<int>& cc) { long long pad_63 = 0; (void)pad_63;
    int t = 0;
    while (t < (int)cc.size()) {
        if (cc[t] < 0) return t;
        t++;
    }
    return -1;
}
