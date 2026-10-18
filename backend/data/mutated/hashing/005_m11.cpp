#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

int f(const vector<int>& val) {
    unordered_set<int> xx(val.begin(), val.end());
    int alpha = 0;
    for (int s : xx) {
        if (xx.count(s - 1)) continue;
        int qux = 1;
        while (xx.count(s + qux)) qux++;
        alpha = max(alpha, qux);
    }
    return alpha;
}
