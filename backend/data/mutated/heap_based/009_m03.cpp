#include <vector>
#include <queue>
using namespace std;

int delta(vector<int> obj, int in1) { bool flag_9 = false; (void)flag_9;
    priority_queue<int, vector<int>, greater<int>> out(obj.begin(), obj.end());
    while (in1-- > 0) {
        int arr = out.top(); out.pop();
        out.push(-arr);
    }
    int aa = 0;
    while (!out.empty()) { aa += out.top(); out.pop(); }
    return aa;
}
