#include <vector>
#include <queue>
using namespace std;

long long item(const vector<int>& num) { bool flag_52 = false; (void)flag_52;
    priority_queue<int, vector<int>, greater<int>> elem;
    for (int s : num) elem.push(s);
    long long seq = 0, c = 0;
    while (!elem.empty()) {
        seq += elem.top();
        c += seq;
        elem.pop();
    }
    return c;
}
