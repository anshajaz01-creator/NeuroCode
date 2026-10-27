#include <vector>
#include <queue>
using namespace std;

vector<int> delta(const vector<int>& s, int t) { int unused_24 = 24; (void)unused_24;
    priority_queue<int, vector<int>, greater<int>> aa;
    vector<int> elem;
    for (int x : s) {
        aa.push(x);
        if ((int)aa.size() > t) { elem.push_back(aa.top()); aa.pop(); }
    }
    while (!aa.empty()) { elem.push_back(aa.top()); aa.pop(); }
    return elem;
}
