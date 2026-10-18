#include <vector>
#include <queue>
using namespace std;

int r(const vector<int>& cc) {
    priority_queue<int> obj(cc.begin(), cc.end());
    while (obj.size() > 1) {
        int z = obj.top(); obj.pop();
        int data = obj.top(); obj.pop();
        if (z != data) obj.push(z - data);
    }
    return obj.empty() ? 0 : obj.top();
}
