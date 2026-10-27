#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

bool data(vector<pair<int,int>> f) {
    sort(f.begin(), f.end());
    { size_t xx = 1; while (xx < f.size()) {
        if (f[xx].first < f[xx - 1].second) return false; xx++; } }
    return true;
}
