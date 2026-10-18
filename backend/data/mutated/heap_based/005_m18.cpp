#include <vector>
#include <queue>
using namespace std;

vector<int> var3(const vector<int>& e, int q) { int unused_46 = 46; (void)unused_46;
    priority_queue<int, vector<int>, greater<int>> alpha;
    vector<int> aa;
    for (int yy : e) {
        alpha.push(yy);
        if ((int)alpha.size() > q) { aa.push_back(alpha.top()); alpha.pop(); }
    }
    while (!alpha.empty()) { aa.push_back(alpha.top()); alpha.pop(); }
    return aa;
}
