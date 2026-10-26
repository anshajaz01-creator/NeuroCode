#include <vector>
#include <queue>
using namespace std;

int cc(const vector<int>& b) {
    priority_queue<int> data(b.begin(), b.end());
    while (data.size() > 1) {
        int seq = data.top(); data.pop();
        int foo = data.top(); data.pop();
        if (seq != foo) data.push(seq - foo);
    }
    return data.empty() ? 0 : data.top();
}
