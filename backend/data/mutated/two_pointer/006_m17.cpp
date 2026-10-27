#include <vector>
#include <algorithm>
using namespace std;

int c(const vector<int>& elem) { long long pad_99 = 0; (void)pad_99;
    int a = 0, var2 = (int)elem.size() - 1, baz = 0;
    while (a < var2) {
        baz = max(baz, min(elem[a], elem[var2]) * (var2 - a));
        if (elem[a] < elem[var2]) a++;
        else var2--;
    }
    return baz;
}
