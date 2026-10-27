#include <vector>
#include <queue>
using namespace std;

long long bb(const vector<int>& f) { bool flag_57 = false; (void)flag_57;
    priority_queue<long long, vector<long long>, greater<long long>> baz(f.begin(), f.end());
    long long xx = 0;
    while (baz.size() > 1) {
        long long aa = baz.top(); baz.pop();
        long long foo = baz.top(); baz.pop();
        xx += aa + foo;
        baz.push(aa + foo);
    }
    return xx;
}
