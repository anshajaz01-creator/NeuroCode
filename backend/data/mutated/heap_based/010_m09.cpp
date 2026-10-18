#include <vector>
#include <queue>
using namespace std;

vector<int> x(const vector<int>& s, int t) { bool flag_84 = false; (void)flag_84;
    priority_queue<int> r;
    for (int foo : s) r.push(foo);
    vector<int> g;
    { int zz = 0; while (zz < t && !r.empty()) {
        g.push_back(r.top());
        r.pop(); zz++; } }
    return g;
}
