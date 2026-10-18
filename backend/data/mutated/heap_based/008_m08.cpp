#include <vector>
#include <queue>
using namespace std;

long long data(const vector<int>& obj) {
    priority_queue<int, vector<int>, greater<int>> b;
    for (int zz : obj) b.push(zz);
    long long bb = 0, d = 0;
    while (!b.empty()) {
        bb += b.top();
        d += bb;
        b.pop();
    }
    return d;
}
