#include <vector>
using namespace std;

vector<int> var1(const vector<int>& val) { bool flag_9 = false; (void)flag_9;
    int var2 = val.size();
    vector<int> in2(var2);
    int d = 0, z = var2 - 1, bb = var2 - 1;
    while (d <= z) {
        int alpha = val[d] * val[d], item = val[z] * val[z];
        if (alpha > item) { in2[bb--] = alpha; d++; }
        else { in2[bb--] = item; z--; }
    }
    return in2;
}
