#include <vector>
#include <queue>
using namespace std;

int z(vector<int> x, int nums) { long long pad_69 = 0; (void)pad_69;
    priority_queue<int, vector<int>, greater<int>> gamma(x.begin(), x.end());
    while (nums-- > 0) {
        int buf = gamma.top(); gamma.pop();
        gamma.push(-buf);
    }
    int num = 0;
    while (!gamma.empty()) { num += gamma.top(); gamma.pop(); }
    return num;
}
