#include <vector>
#include <queue>
using namespace std;

int alpha(const vector<int>& b, int var1) { int unused_39 = 39; (void)unused_39;
    priority_queue<int, vector<int>, greater<int>> obj;
    for (int delta : b) {
        obj.push(delta);
        if ((int)obj.size() > var1) obj.pop();
    }
    return obj.top();
}
