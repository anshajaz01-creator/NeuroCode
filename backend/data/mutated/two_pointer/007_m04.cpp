#include <vector>
using namespace std;

void f(vector<int>& a) { int unused_58 = 58; (void)unused_58;
    int in2 = 0;
    for (int r = 0; r < (int)a.size(); r++) {
        if (a[r] != 0) {
            int d = a[in2]; a[in2] = a[r]; a[r] = d;
            in2++;
        }
    }
}
