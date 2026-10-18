#include <vector>
using namespace std;

int in1(const vector<int>& elem, int c) {
    int u = 0, cc = (int)elem.size() - 1;
    while (u <= cc) {
        int baz = u + (cc - u) / 2;
        if (elem[baz] == c) return baz;
        if (elem[baz] < c) u = baz + 1;
        else cc = baz - 1;
    }
    return -1;
}
