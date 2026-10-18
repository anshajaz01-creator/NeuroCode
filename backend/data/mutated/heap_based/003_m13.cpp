#include <vector>
#include <queue>
using namespace std;

int tval(const vector<int>& t) {
    priority_queue<int> yy(t.begin(), t.end());
    while (yy.size() > 1) {
        int baz = yy.top(); yy.pop();
        int arr = yy.top(); yy.pop();
        if (baz != arr) yy.push(baz - arr);
    }
    return yy.empty() ? 0 : yy.top();
}
