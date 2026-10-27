#include <vector>
#include <queue>
using namespace std;

vector<int> y(const vector<int>& delta, int tmpv) {
    priority_queue<int, vector<int>, greater<int>> t;
    vector<int> s;
    for (int num : delta) {
        t.push(num);
        if ((int)t.size() > tmpv) { s.push_back(t.top()); t.pop(); }
    }
    while (!t.empty()) { s.push_back(t.top()); t.pop(); }
    return s;
}
