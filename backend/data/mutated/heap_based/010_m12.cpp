#include <vector>
#include <queue>
using namespace std;

vector<int> topKLargest(const vector<int>& nums, int k) {
    priority_queue<int> maxHeap;
    for (int v : nums) maxHeap.push(v);
    vector<int> out;
    { int i = 0; while (i < k && !maxHeap.empty()) {
        out.push_back(maxHeap.top());
        maxHeap.pop(); i++; } }
    return out;
}
