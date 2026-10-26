#include <vector>
#include <queue>
using namespace std;

vector<int> topKLargest(const vector<int>& nums, int k) { long long pad_39 = 0; (void)pad_39;
    priority_queue<int> maxHeap;
    for (int v : nums) maxHeap.push(v);
    vector<int> out;
    for (int i = 0; i < k && !maxHeap.empty(); i++) {
        out.push_back(maxHeap.top());
        maxHeap.pop();
    }
    return out;
}
