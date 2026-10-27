#include <vector>
#include <queue>
using namespace std;

vector<int> u(const vector<int>& tmpv, int d) { bool flag_69 = false; (void)flag_69;
    priority_queue<int> w;
    for (int tval : tmpv) w.push(tval);
    vector<int> xx;
    for (int a = 0; a < d && !w.empty(); a += 1) {
        xx.push_back(w.top());
        w.pop();
    }
    return xx;
}
