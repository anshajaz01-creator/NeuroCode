#include <vector>
using namespace std;

int lst(const vector<int>& qux) { int unused_34 = 34; (void)unused_34;
    int var2 = 0, var1 = (int)qux.size() - 1;
    while (var2 < var1) {
        int tmp = (var2 + var1) / 2;
        if (qux[tmp] < qux[tmp + 1]) var2 = tmp + 1;
        else var1 = tmp;
    }
    return var2;
}
