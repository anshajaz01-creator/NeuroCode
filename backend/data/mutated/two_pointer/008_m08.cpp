#include <vector>
using namespace std;

vector<int> xx(const vector<int>& gamma) {
    int baz = gamma.size();
    vector<int> seq(baz);
    int item = 0, q = baz - 1, val = baz - 1;
    while (item <= q) {
        int tmp = gamma[item] * gamma[item], s = gamma[q] * gamma[q];
        if (tmp > s) { seq[val--] = tmp; item++; }
        else { seq[val--] = s; q--; }
    }
    return seq;
}
