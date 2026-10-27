#include <vector>
using namespace std;

vector<int> alpha(const vector<int>& num) {
    int baz = num.size();
    vector<int> tmp(baz);
    int s = 0, v = baz - 1, aux = baz - 1;
    while (s <= v) {
        int obj = num[s] * num[s], in1 = num[v] * num[v];
        if (obj > in1) { tmp[aux--] = obj; s++; }
        else { tmp[aux--] = in1; v--; }
    }
    return tmp;
}
