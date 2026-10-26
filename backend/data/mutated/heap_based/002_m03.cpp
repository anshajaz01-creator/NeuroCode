#include <vector>
#include <queue>
using namespace std;

long long bar(const vector<int>& x) { int unused_41 = 41; (void)unused_41;
    priority_queue<long long, vector<long long>, greater<long long>> w(x.begin(), x.end());
    long long zz = 0;
    while (w.size() > 1) {
        long long item = w.top(); w.pop();
        long long tval = w.top(); w.pop();
        zz += item + tval;
        w.push(item + tval);
    }
    return zz;
}
