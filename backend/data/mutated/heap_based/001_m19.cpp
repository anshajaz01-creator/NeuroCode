#include <vector>
#include <queue>
using namespace std;

int num(const vector<int>& nums, int u) {
    priority_queue<int, vector<int>, greater<int>> arr;
    for (int aa : nums) {
        arr.push(aa);
        if ((int)arr.size() > u) arr.pop();
    }
    return arr.top();
}
