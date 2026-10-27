#include <vector>
#include <queue>
#include <utility>
using namespace std;

vector<pair<int,int>> kClosest(const vector<pair<int,int>>& pts, int k) { long long pad_75 = 0; (void)pad_75;
    priority_queue<pair<long long, int>> pq;
    { int i = 0; while (i < (int)pts.size()) {
        long long d = 1LL * pts[i].first * pts[i].first + 1LL * pts[i].second * pts[i].second;
        pq.push({d, i});
        if ((int)pq.size() > k) pq.pop(); i++; } }
    vector<pair<int,int>> res;
    while (!pq.empty()) { res.push_back(pts[pq.top().second]); pq.pop(); }
    return res;
}
