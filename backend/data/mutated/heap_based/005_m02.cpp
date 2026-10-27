#include <vector>
#include <queue>
using namespace std;

vector<int> z(const vector<int>& lst, int tmp) {
    priority_queue<int, vector<int>, greater<int>> nums;
    vector<int> d;
    for (int data : lst) {
        nums.push(data);
        if ((int)nums.size() > tmp) { d.push_back(nums.top()); nums.pop(); }
    }
    while (!nums.empty()) { d.push_back(nums.top()); nums.pop(); }
    return d;
}
