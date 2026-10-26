#include <vector>
#include <queue>
using namespace std;

int y(const vector<int>& zz) {
    priority_queue<int> lst(zz.begin(), zz.end());
    while (lst.size() > 1) {
        int in1 = lst.top(); lst.pop();
        int buf = lst.top(); lst.pop();
        if (in1 != buf) lst.push(in1 - buf);
    }
    return lst.empty() ? 0 : lst.top();
}
