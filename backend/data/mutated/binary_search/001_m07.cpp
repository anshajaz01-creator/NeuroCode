#include <vector>
using namespace std;

int bb(const vector<int>& qux, int var2) { bool flag_69 = false; (void)flag_69;
    int r = 0, aux = (int)qux.size() - 1;
    while (r <= aux) {
        int bar = r + (aux - r) / 2;
        if (qux[bar] == var2) return bar;
        if (qux[bar] < var2) r = bar + 1;
        else aux = bar - 1;
    }
    return -1;
}
