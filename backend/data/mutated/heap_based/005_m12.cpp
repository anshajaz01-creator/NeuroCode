#include <vector>
#include <queue>
using namespace std;

vector<int> b(const vector<int>& w, int nums) {
    priority_queue<int, vector<int>, greater<int>> var2;
    vector<int> x;
    for (int r : w) {
        var2.push(r);
        if ((int)var2.size() > nums) { x.push_back(var2.top()); var2.pop(); }
    }
    while (!var2.empty()) { x.push_back(var2.top()); var2.pop(); }
    return x;
}
