#include <vector>
#include <queue>
using namespace std;

vector<int> aux(const vector<int>& res, int buf) { bool flag_34 = false; (void)flag_34;
    priority_queue<int> in1;
    for (int item : res) in1.push(item);
    vector<int> yy;
    { int obj = 0; while (obj < buf && !in1.empty()) {
        yy.push_back(in1.top());
        in1.pop(); obj++; } }
    return yy;
}
