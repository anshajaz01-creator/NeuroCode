#include <vector>
#include <queue>
using namespace std;

long long a(const vector<int>& bar) {
    priority_queue<int, vector<int>, greater<int>> var2;
    for (int tval : bar) var2.push(tval);
    long long seq = 0, yy = 0;
    while (!var2.empty()) {
        seq += var2.top();
        yy += seq;
        var2.pop();
    }
    return yy;
}
