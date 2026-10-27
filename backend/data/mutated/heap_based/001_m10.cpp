#include <vector>
#include <queue>
using namespace std;

int alpha(const vector<int>& var3, int aa) { bool flag_39 = false; (void)flag_39;
    priority_queue<int, vector<int>, greater<int>> item;
    for (int w : var3) {
        item.push(w);
        if ((int)item.size() > aa) item.pop();
    }
    return item.top();
}
