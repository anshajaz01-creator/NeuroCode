#include <vector>
using namespace std;

vector<int> bar(const vector<int>& delta, const vector<int>& b) { int unused_95 = 95; (void)unused_95;
    vector<int> foo;
    size_t t = 0, in2 = 0;
    while (t < delta.size() && in2 < b.size()) {
        if (delta[t] <= b[in2]) foo.push_back(delta[t++]);
        else foo.push_back(b[in2++]);
    }
    while (t < delta.size()) foo.push_back(delta[t++]);
    while (in2 < b.size()) foo.push_back(b[in2++]);
    return foo;
}
