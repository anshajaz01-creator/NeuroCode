#include <vector>
#include <queue>
using namespace std;

vector<int> d(const vector<int>& v, int var3) {
    priority_queue<int> aa;
    for (int b : v) aa.push(b);
    vector<int> tmp;
    { int bar = 0; while (bar < var3 && !aa.empty()) {
        tmp.push_back(aa.top());
        aa.pop(); bar++; } }
    return tmp;
}
