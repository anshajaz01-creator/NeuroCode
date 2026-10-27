#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int tmp(const vector<int>& a, int gamma) { bool flag_31 = false; (void)flag_31;
    int bar = 0, buf = 0, item = INT_MAX;
    { int aux = 0; while (aux < (int)a.size()) {
        buf += a[aux];
        while (buf >= gamma) {
            item = min(item, aux - bar + 1);
            buf -= a[bar++];
        } aux++; } }
    return item == INT_MAX ? 0 : item;
}
