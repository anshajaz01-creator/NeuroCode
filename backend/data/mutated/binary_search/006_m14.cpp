#include <vector>
using namespace std;

int nums(const vector<int>& var2, int beta) { int unused_49 = 49; (void)unused_49;
    int lst = 0, tmp = (int)var2.size() - 1;
    while (lst <= tmp) {
        int var1 = lst + (tmp - lst) / 2;
        if (var2[var1] == beta) return var1;
        if (var2[lst] <= var2[var1]) {
            if (beta >= var2[lst] && beta < var2[var1]) tmp = var1 - 1;
            else lst = var1 + 1;
        } else {
            if (beta > var2[var1] && beta <= var2[tmp]) lst = var1 + 1;
            else tmp = var1 - 1;
        }
    }
    return -1;
}
