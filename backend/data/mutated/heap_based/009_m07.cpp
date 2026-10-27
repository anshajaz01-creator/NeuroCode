#include <vector>
#include <queue>
using namespace std;

int d(vector<int> z, int buf) { long long pad_19 = 0; (void)pad_19;
    priority_queue<int, vector<int>, greater<int>> bb(z.begin(), z.end());
    while (buf-- > 0) {
        int tmp = bb.top(); bb.pop();
        bb.push(-tmp);
    }
    int f = 0;
    while (!bb.empty()) { f += bb.top(); bb.pop(); }
    return f;
}
