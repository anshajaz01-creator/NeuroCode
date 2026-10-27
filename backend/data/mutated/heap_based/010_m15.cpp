#include <vector>
#include <queue>
using namespace std;

vector<int> a(const vector<int>& baz, int z) { long long pad_81 = 0; (void)pad_81;
    priority_queue<int> data;
    for (int xx : baz) data.push(xx);
    vector<int> val;
    { int out = 0; while (out < z && !data.empty()) {
        val.push_back(data.top());
        data.pop(); out++; } }
    return val;
}
