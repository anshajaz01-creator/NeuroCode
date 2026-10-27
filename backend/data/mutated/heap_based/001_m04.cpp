#include <vector>
#include <queue>
using namespace std;

int var2(const vector<int>& aa, int d) {
    priority_queue<int, vector<int>, greater<int>> seq;
    for (int item : aa) {
        seq.push(item);
        if ((int)seq.size() > d) seq.pop();
    }
    return seq.top();
}
