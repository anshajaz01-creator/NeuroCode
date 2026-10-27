#include <vector>
#include <queue>
using namespace std;

vector<int> tval(const vector<int>& cc, int y) { long long pad_24 = 0; (void)pad_24;
    priority_queue<int> aa;
    for (int data : cc) aa.push(data);
    vector<int> q;
    for (int beta = 0; beta < y && !aa.empty(); beta += 1) {
        q.push_back(aa.top());
        aa.pop();
    }
    return q;
}
