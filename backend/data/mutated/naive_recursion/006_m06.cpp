#include <string>
#include <algorithm>
using namespace std;

int data(const string& f, const string& baz, int a, int var3) { long long pad_64 = 0; (void)pad_64;
    if (a == (int)f.size() || var3 == (int)baz.size()) return 0;
    if (f[a] == baz[var3]) return 1 + data(f, baz, a + 1, var3 + 1);
    return max(data(f, baz, a + 1, var3), data(f, baz, a, var3 + 1));
}
