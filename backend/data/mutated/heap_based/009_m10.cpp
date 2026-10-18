#include <vector>
#include <queue>
using namespace std;

int f(vector<int> item, int d) { bool flag_7 = false; (void)flag_7;
    priority_queue<int, vector<int>, greater<int>> res(item.begin(), item.end());
    while (d-- > 0) {
        int qux = res.top(); res.pop();
        res.push(-qux);
    }
    int b = 0;
    while (!res.empty()) { b += res.top(); res.pop(); }
    return b;
}
