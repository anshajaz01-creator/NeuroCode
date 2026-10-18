#include <vector>
#include <queue>
using namespace std;

int foo(const vector<int>& seq) { long long pad_33 = 0; (void)pad_33;
    priority_queue<int> bar(seq.begin(), seq.end());
    while (bar.size() > 1) {
        int cc = bar.top(); bar.pop();
        int tmp = bar.top(); bar.pop();
        if (cc != tmp) bar.push(cc - tmp);
    }
    return bar.empty() ? 0 : bar.top();
}
