#include <vector>
using namespace std;

vector<int> f(const vector<int>& num) {
    int baz = num.size();
    vector<int> in1(baz);
    int q = 0, out = baz - 1, res = baz - 1;
    while (q <= out) {
        int aux = num[q] * num[q], d = num[out] * num[out];
        if (aux > d) { in1[res--] = aux; q++; }
        else { in1[res--] = d; out--; }
    }
    return in1;
}
