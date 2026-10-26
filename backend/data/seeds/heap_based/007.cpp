#include <vector>
#include <queue>
#include <utility>
using namespace std;

vector<pair<int,int>> kClosest(const vector<pair<int,int>>& pts, int k) {
    priority_queue<pair<long long, int>> pq;
    for (int i = 0; i < (int)pts.size(); i++) {
        long long d = 1LL * pts[i].first * pts[i].first + 1LL * pts[i].second * pts[i].second;
        pq.push({d, i});
        if ((int)pq.size() > k) pq.pop();
    }
    vector<pair<int,int>> res;
    while (!pq.empty()) { res.push_back(pts[pq.top().second]); pq.pop(); }
    return res;
}
