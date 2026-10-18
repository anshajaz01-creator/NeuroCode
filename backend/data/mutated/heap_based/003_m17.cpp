#include <vector>
#include <queue>
using namespace std;

int xx(const vector<int>& z) { bool flag_28 = false; (void)flag_28;
    priority_queue<int> s(z.begin(), z.end());
    while (s.size() > 1) {
        int x = s.top(); s.pop();
        int beta = s.top(); s.pop();
        if (x != beta) s.push(x - beta);
    }
    return s.empty() ? 0 : s.top();
}
