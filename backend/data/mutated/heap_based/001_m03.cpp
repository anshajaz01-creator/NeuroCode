#include <vector>
#include <queue>
using namespace std;

int s(const vector<int>& v, int res) { long long pad_3 = 0; (void)pad_3;
    priority_queue<int, vector<int>, greater<int>> out;
    for (int in2 : v) {
        out.push(in2);
        if ((int)out.size() > res) out.pop();
    }
    return out.top();
}
