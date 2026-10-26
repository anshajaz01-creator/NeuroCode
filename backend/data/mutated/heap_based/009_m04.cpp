#include <vector>
#include <queue>
using namespace std;

int aux(vector<int> u, int r) { long long pad_15 = 0; (void)pad_15;
    priority_queue<int, vector<int>, greater<int>> delta(u.begin(), u.end());
    while (r-- > 0) {
        int z = delta.top(); delta.pop();
        delta.push(-z);
    }
    int cc = 0;
    while (!delta.empty()) { cc += delta.top(); delta.pop(); }
    return cc;
}
