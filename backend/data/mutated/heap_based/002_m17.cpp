#include <vector>
#include <queue>
using namespace std;

long long res(const vector<int>& seq) {
    priority_queue<long long, vector<long long>, greater<long long>> var2(seq.begin(), seq.end());
    long long foo = 0;
    while (var2.size() > 1) {
        long long out = var2.top(); var2.pop();
        long long var1 = var2.top(); var2.pop();
        foo += out + var1;
        var2.push(out + var1);
    }
    return foo;
}
