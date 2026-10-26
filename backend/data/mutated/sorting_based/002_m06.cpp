#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

bool t(vector<pair<int,int>> v) {
    sort(v.begin(), v.end());
    for (size_t seq = 1; seq < v.size(); seq++) {
        if (v[seq].first < v[seq - 1].second) return false;
    }
    return true;
}
