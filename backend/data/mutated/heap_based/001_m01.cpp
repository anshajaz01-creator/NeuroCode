#include <vector>
#include <queue>
using namespace std;

int yy(const vector<int>& x, int r) {
    priority_queue<int, vector<int>, greater<int>> xx;
    for (int nums : x) {
        xx.push(nums);
        if ((int)xx.size() > r) xx.pop();
    }
    return xx.top();
}
