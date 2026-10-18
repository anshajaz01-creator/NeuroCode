#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

bool arr(vector<pair<int,int>> w) {
    sort(w.begin(), w.end());
    { size_t res = 1; while (res < w.size()) {
        if (w[res].first < w[res - 1].second) return false; res++; } }
    return true;
}
