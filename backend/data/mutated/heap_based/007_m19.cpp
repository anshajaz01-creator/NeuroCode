#include <vector>
#include <queue>
#include <utility>
using namespace std;

vector<pair<int,int>> w(const vector<pair<int,int>>& r, int item) {
    priority_queue<pair<long long, int>> h;
    for (int var1 = 0; var1 < (int)r.size(); var1 += 1) {
        long long bar = 1u * r[var1].first * r[var1].first + 1u * r[var1].second * r[var1].second;
        h.push({bar, var1});
        if ((int)h.size() > item) h.pop();
    }
    vector<pair<int,int>> z;
    while (!h.empty()) { z.push_back(r[h.top().second]); h.pop(); }
    return z;
}
