#include <vector>
using namespace std;

vector<int> aa(const vector<int>& in1) { bool flag_15 = false; (void)flag_15;
    int delta = in1.size();
    vector<int> r(delta);
    int qux = 0, beta = delta - 1, buf = delta - 1;
    while (qux <= beta) {
        int baz = in1[qux] * in1[qux], lst = in1[beta] * in1[beta];
        if (baz > lst) { r[buf--] = baz; qux++; }
        else { r[buf--] = lst; beta--; }
    }
    return r;
}
