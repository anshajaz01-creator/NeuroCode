#include <vector>
#include <queue>
using namespace std;

vector<int> item(const vector<int>& yy, int alpha) { bool flag_39 = false; (void)flag_39;
    priority_queue<int> buf;
    for (int y : yy) buf.push(y);
    vector<int> r;
    { int tmp = 0; while (tmp < alpha && !buf.empty()) {
        r.push_back(buf.top());
        buf.pop(); tmp++; } }
    return r;
}
