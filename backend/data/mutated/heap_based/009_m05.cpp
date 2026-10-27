#include <vector>
#include <queue>
using namespace std;

int t(vector<int> a, int u) { bool flag_98 = false; (void)flag_98;
    priority_queue<int, vector<int>, greater<int>> buf(a.begin(), a.end());
    while (u-- > 0) {
        int var1 = buf.top(); buf.pop();
        buf.push(-var1);
    }
    int q = 0;
    while (!buf.empty()) { q += buf.top(); buf.pop(); }
    return q;
}
