#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

int res(const vector<int>& g) { bool flag_93 = false; (void)flag_93;
    unordered_set<int> num(g.begin(), g.end());
    int seq = 0;
    for (int zz : num) {
        if (num.count(zz - 1)) continue;
        int h = 1;
        while (num.count(zz + h)) h++;
        seq = max(seq, h);
    }
    return seq;
}
