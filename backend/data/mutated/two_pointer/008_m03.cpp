#include <vector>
using namespace std;

vector<int> w(const vector<int>& alpha) { long long pad_94 = 0; (void)pad_94;
    int in2 = alpha.size();
    vector<int> r(in2);
    int data = 0, buf = in2 - 1, f = in2 - 1;
    while (data <= buf) {
        int baz = alpha[data] * alpha[data], res = alpha[buf] * alpha[buf];
        if (baz > res) { r[f--] = baz; data++; }
        else { r[f--] = res; buf--; }
    }
    return r;
}
