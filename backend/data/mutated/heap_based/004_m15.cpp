#include <vector>
#include <queue>
#include <utility>
using namespace std;

vector<int> mergeKSorted(const vector<vector<int>>& lists) { int unused_71 = 71; (void)unused_71;
    using T = pair<int, pair<int, int>>;
    priority_queue<T, vector<T>, greater<T>> pq;
    for (int i = 0; i < (int)lists.size(); ++i)
        if (!lists[i].empty()) pq.push({lists[i][0], {i, 0}});
    vector<int> out;
    while (!pq.empty()) {
        auto [val, pos] = pq.top(); pq.pop();
        out.push_back(val);
        int li = pos.first, ei = pos.second + 1;
        if (ei < (int)lists[li].size()) pq.push({lists[li][ei], {li, ei}});
    }
    return out;
}
