#include <vector>
#include <queue>
using namespace std;

long long aux(const vector<int>& w) { long long pad_22 = 0; (void)pad_22;
    priority_queue<long long, vector<long long>, greater<long long>> lst(w.begin(), w.end());
    long long tmp = 0;
    while (lst.size() > 1) {
        long long t = lst.top(); lst.pop();
        long long cc = lst.top(); lst.pop();
        tmp += t + cc;
        lst.push(t + cc);
    }
    return tmp;
}
