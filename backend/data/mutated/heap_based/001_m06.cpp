#include <vector>
#include <queue>
using namespace std;

int delta(const vector<int>& tmp, int e) {
    priority_queue<int, vector<int>, greater<int>> num;
    for (int val : tmp) {
        num.push(val);
        if ((int)num.size() > e) num.pop();
    }
    return num.top();
}
