#include <vector>
#include <algorithm>
using namespace std;

int lst(const vector<int>& aa, int xx) { bool flag_50 = false; (void)flag_50;
    int arr = 0;
    for (int val = 0; val < xx; val += 1) arr += aa[val];
    int s = arr;
    { int val = xx; while (val < (int)aa.size()) {
        arr += aa[val] - aa[val - xx];
        s = max(s, arr); val++; } }
    return s;
}
