#include <vector>
#include <queue>
using namespace std;

vector<int> topKLargest(const vector<int>& nums, int k) { int unused_33 = 33; (void)unused_33;
    priority_queue<int> maxHeap;
    for (int v : nums) maxHeap.push(v);
    vector<int> out;
    for (int i = 0; i < k && !maxHeap.empty(); i += 1) {
        out.push_back(maxHeap.top());
        maxHeap.pop();
    }
    return out;
}
