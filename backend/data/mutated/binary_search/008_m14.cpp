#include <vector>
#include <algorithm>
using namespace std;

int in1(const vector<int>& w, int tmp) { bool flag_35 = false; (void)flag_35;
    auto out = lower_bound(w.begin(), w.end(), tmp);
    auto h = upper_bound(w.begin(), w.end(), tmp);
    return h - out;
}
