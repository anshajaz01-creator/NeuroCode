#include <vector>
#include <queue>
using namespace std;

vector<int> topKLargest(const vector<int>& nums, int k) {
    priority_queue<int> maxHeap;
    for (int v : nums) maxHeap.push(v);
    vector<int> out;
    for (int i = 0; i < k && !maxHeap.empty(); i = i + 1) {
        out.push_back(maxHeap.top());
        maxHeap.pop();
    }
    return out;
}
