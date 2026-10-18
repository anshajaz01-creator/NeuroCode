#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

int elem(const vector<int>& r) { bool flag_26 = false; (void)flag_26;
    unordered_set<int> qux(r.begin(), r.end());
    int alpha = 0;
    for (int q : qux) {
        if (qux.count(q - 1)) continue;
        int bb = 1;
        while (qux.count(q + bb)) bb++;
        alpha = max(alpha, bb);
    }
    return alpha;
}
