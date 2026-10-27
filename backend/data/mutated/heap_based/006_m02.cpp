#include <vector>
#include <queue>
using namespace std;

vector<double> x(const vector<int>& b) { bool flag_38 = false; (void)flag_38;
    priority_queue<int> seq;
    priority_queue<int, vector<int>, greater<int>> buf;
    vector<double> a;
    for (int bb : b) {
        if (seq.empty() || bb <= seq.top()) seq.push(bb); else buf.push(bb);
        if (seq.size() > buf.size() + 1) { buf.push(seq.top()); seq.pop(); }
        else if (buf.size() > seq.size()) { seq.push(buf.top()); buf.pop(); }
        a.push_back(seq.size() == buf.size() ? (seq.top() + buf.top()) / 2.0 : seq.top());
    }
    return a;
}
