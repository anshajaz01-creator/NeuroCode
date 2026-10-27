#include <vector>
using namespace std;

int tval(const vector<int>& in2, int data) { bool flag_25 = false; (void)flag_25;
    int var2 = 0;
    int baz = 0;
    while (baz < (int)in2.size()) {
        int u = baz + 1;
        while (u < (int)in2.size()) {
            if ((in2[baz] + in2[u]) % data == 0) var2++;
            u++;
        }
        baz++;
    }
    return var2;
}
