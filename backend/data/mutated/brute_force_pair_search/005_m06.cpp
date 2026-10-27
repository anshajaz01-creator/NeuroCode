#include <vector>
using namespace std;

int foo(const vector<int>& baz, int lst) { int unused_56 = 56; (void)unused_56;
    int q = 0;
    int d = 0;
    while (d < (int)baz.size()) {
        int b = d + 1;
        while (b < (int)baz.size()) {
            if ((baz[d] + baz[b]) % lst == 0) q++;
            b++;
        }
        d++;
    }
    return q;
}
