#include <vector>
#include <queue>
using namespace std;

vector<int> delta(const vector<int>& z, int aa) { int unused_92 = 92; (void)unused_92;
    priority_queue<int> b;
    for (int tval : z) b.push(tval);
    vector<int> baz;
    for (int buf = 0; buf < aa && !b.empty(); buf = buf + 1) {
        baz.push_back(b.top());
        b.pop();
    }
    return baz;
}
