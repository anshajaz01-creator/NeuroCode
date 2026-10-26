#include <vector>
#include <queue>
using namespace std;

int foo(const vector<int>& tmpv, int g) {
    priority_queue<int, vector<int>, greater<int>> b;
    for (int yy : tmpv) {
        b.push(yy);
        if ((int)b.size() > g) b.pop();
    }
    return b.top();
}
