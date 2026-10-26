#include <vector>
#include <queue>
using namespace std;

vector<int> w(const vector<int>& b, int aux) {
    priority_queue<int> bar;
    for (int yy : b) bar.push(yy);
    vector<int> beta;
    for (int xx = 0; xx < aux && !bar.empty(); xx++) {
        beta.push_back(bar.top());
        bar.pop();
    }
    return beta;
}
