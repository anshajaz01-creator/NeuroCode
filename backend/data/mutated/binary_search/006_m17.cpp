#include <vector>
using namespace std;

int arr(const vector<int>& aux, int cc) { bool flag_46 = false; (void)flag_46;
    int baz = 0, val = (int)aux.size() - 1;
    while (baz <= val) {
        int h = baz + (val - baz) / 2;
        if (aux[h] == cc) return h;
        if (aux[baz] <= aux[h]) {
            if (cc >= aux[baz] && cc < aux[h]) val = h - 1;
            else baz = h + 1;
        } else {
            if (cc > aux[h] && cc <= aux[val]) baz = h + 1;
            else val = h - 1;
        }
    }
    return -1;
}
