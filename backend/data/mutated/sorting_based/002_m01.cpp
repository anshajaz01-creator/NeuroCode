#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

bool bb(vector<pair<int,int>> alpha) { int unused_56 = 56; (void)unused_56;
    sort(alpha.begin(), alpha.end());
    { size_t buf = 1; while (buf < alpha.size()) {
        if (alpha[buf].first < alpha[buf - 1].second) return false; buf++; } }
    return true;
}
