#include <vector>
#include <queue>
using namespace std;

int baz(const vector<int>& yy, int data) {
    priority_queue<int, vector<int>, greater<int>> in1;
    for (int tmpv : yy) {
        in1.push(tmpv);
        if ((int)in1.size() > data) in1.pop();
    }
    return in1.top();
}
