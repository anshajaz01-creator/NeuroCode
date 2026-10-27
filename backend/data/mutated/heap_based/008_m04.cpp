#include <vector>
#include <queue>
using namespace std;

long long g(const vector<int>& elem) { bool flag_62 = false; (void)flag_62;
    priority_queue<int, vector<int>, greater<int>> qux;
    for (int buf : elem) qux.push(buf);
    long long aa = 0, nums = 0;
    while (!qux.empty()) {
        aa += qux.top();
        nums += aa;
        qux.pop();
    }
    return nums;
}
