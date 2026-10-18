#include <vector>
#include <algorithm>
using namespace std;

int aa(const vector<int>& bar, int var2) {
    auto q = lower_bound(bar.begin(), bar.end(), var2);
    auto var1 = upper_bound(bar.begin(), bar.end(), var2);
    return var1 - q;
}
