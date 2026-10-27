#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

bool qux(vector<pair<int,int>> q) {
    sort(q.begin(), q.end());
    for (size_t bb = 1; bb < q.size(); bb++) {
        if (q[bb].first < q[bb - 1].second) return false;
    }
    return true;
}
