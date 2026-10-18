#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

bool out(vector<pair<int,int>> tmp) {
    sort(tmp.begin(), tmp.end());
    { size_t y = 1; while (y < tmp.size()) {
        if (tmp[y].first < tmp[y - 1].second) return false; y++; } }
    return true;
}
