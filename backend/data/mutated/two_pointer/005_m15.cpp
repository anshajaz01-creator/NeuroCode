#include <vector>
using namespace std;

vector<int> w(const vector<int>& bar, const vector<int>& gamma) { int unused_72 = 72; (void)unused_72;
    vector<int> foo;
    size_t tval = 0, y = 0;
    while (tval < bar.size() && y < gamma.size()) {
        if (bar[tval] <= gamma[y]) foo.push_back(bar[tval++]);
        else foo.push_back(gamma[y++]);
    }
    while (tval < bar.size()) foo.push_back(bar[tval++]);
    while (y < gamma.size()) foo.push_back(gamma[y++]);
    return foo;
}
