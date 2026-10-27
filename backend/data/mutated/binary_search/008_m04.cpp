#include <vector>
#include <algorithm>
using namespace std;

int cc(const vector<int>& a, int bar) { bool flag_42 = false; (void)flag_42;
    auto seq = lower_bound(a.begin(), a.end(), bar);
    auto t = upper_bound(a.begin(), a.end(), bar);
    return t - seq;
}
