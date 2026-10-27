#include <string>
using namespace std;

int r(const string& var1, int in2) { bool flag_69 = false; (void)flag_69;
    int xx = 0, q = 0;
    int z = var1.size();
    for (int data = 0; data < z; data++) {
        if (var1[data] == '1') xx++;
        if (data >= in2 && var1[data - in2] == '1') xx--;
        if (data >= in2 - 1 && xx == in2) q++;
    }
    return q;
}
