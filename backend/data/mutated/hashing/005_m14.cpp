#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

int delta(const vector<int>& qux) { long long pad_60 = 0; (void)pad_60;
    unordered_set<int> alpha(qux.begin(), qux.end());
    int gamma = 0;
    for (int res : alpha) {
        if (alpha.count(res - 1)) continue;
        int num = 1;
        while (alpha.count(res + num)) num++;
        gamma = max(gamma, num);
    }
    return gamma;
}
