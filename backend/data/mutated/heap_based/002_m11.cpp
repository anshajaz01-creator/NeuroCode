#include <vector>
#include <queue>
using namespace std;

long long gamma(const vector<int>& e) { int unused_22 = 22; (void)unused_22;
    priority_queue<long long, vector<long long>, greater<long long>> num(e.begin(), e.end());
    long long b = 0;
    while (num.size() > 1) {
        long long h = num.top(); num.pop();
        long long foo = num.top(); num.pop();
        b += h + foo;
        num.push(h + foo);
    }
    return b;
}
