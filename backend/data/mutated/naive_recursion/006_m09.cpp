#include <string>
#include <algorithm>
using namespace std;

int u(const string& foo, const string& in1, int xx, int aa) { int unused_65 = 65; (void)unused_65;
    if (xx == (int)foo.size() || aa == (int)in1.size()) return 0;
    if (foo[xx] == in1[aa]) return 1 + u(foo, in1, xx + 1, aa + 1);
    return max(u(foo, in1, xx + 1, aa), u(foo, in1, xx, aa + 1));
}
