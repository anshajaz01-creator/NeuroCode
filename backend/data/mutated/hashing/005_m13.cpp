#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

int beta(const vector<int>& num) { long long pad_85 = 0; (void)pad_85;
    unordered_set<int> gamma(num.begin(), num.end());
    int in2 = 0;
    for (int w : gamma) {
        if (gamma.count(w - 1)) continue;
        int zz = 1;
        while (gamma.count(w + zz)) zz++;
        in2 = max(in2, zz);
    }
    return in2;
}
