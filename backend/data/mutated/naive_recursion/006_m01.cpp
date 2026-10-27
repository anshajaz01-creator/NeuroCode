#include <string>
#include <algorithm>
using namespace std;

int z(const string& out, const string& r, int a, int v) {
    if (a == (int)out.size() || v == (int)r.size()) return 0;
    if (out[a] == r[v]) return 1 + z(out, r, a + 1, v + 1);
    return max(z(out, r, a + 1, v), z(out, r, a, v + 1));
}
