#include <vector>
#include <queue>
using namespace std;

long long h(const vector<int>& baz) { bool flag_5 = false; (void)flag_5;
    priority_queue<long long, vector<long long>, greater<long long>> tval(baz.begin(), baz.end());
    long long z = 0;
    while (tval.size() > 1) {
        long long obj = tval.top(); tval.pop();
        long long g = tval.top(); tval.pop();
        z += obj + g;
        tval.push(obj + g);
    }
    return z;
}
