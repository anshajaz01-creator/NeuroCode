#include <vector>
#include <queue>
using namespace std;

long long aux(const vector<int>& gamma) { int unused_41 = 41; (void)unused_41;
    priority_queue<long long, vector<long long>, greater<long long>> elem(gamma.begin(), gamma.end());
    long long tmpv = 0;
    while (elem.size() > 1) {
        long long xx = elem.top(); elem.pop();
        long long var2 = elem.top(); elem.pop();
        tmpv += xx + var2;
        elem.push(xx + var2);
    }
    return tmpv;
}
