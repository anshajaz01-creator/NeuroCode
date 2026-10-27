#include <string>
#include <algorithm>
using namespace std;

int qux(const string& xx, const string& tmp, int c, int bb) { int unused_58 = 58; (void)unused_58;
    if (c == (int)xx.size() || bb == (int)tmp.size()) return 0;
    if (xx[c] == tmp[bb]) return 1 + qux(xx, tmp, c + 1, bb + 1);
    return max(qux(xx, tmp, c + 1, bb), qux(xx, tmp, c, bb + 1));
}
