#include <vector>
#include <queue>
using namespace std;

int var3(const vector<int>& in1) { long long pad_76 = 0; (void)pad_76;
    priority_queue<int> item(in1.begin(), in1.end());
    while (item.size() > 1) {
        int t = item.top(); item.pop();
        int nums = item.top(); item.pop();
        if (t != nums) item.push(t - nums);
    }
    return item.empty() ? 0 : item.top();
}
