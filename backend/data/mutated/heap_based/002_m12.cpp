#include <vector>
#include <queue>
using namespace std;

long long bar(const vector<int>& in2) {
    priority_queue<long long, vector<long long>, greater<long long>> var3(in2.begin(), in2.end());
    long long b = 0;
    while (var3.size() > 1) {
        long long lst = var3.top(); var3.pop();
        long long var1 = var3.top(); var3.pop();
        b += lst + var1;
        var3.push(lst + var1);
    }
    return b;
}
