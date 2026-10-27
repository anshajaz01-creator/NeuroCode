#include <vector>
#include <algorithm>
using namespace std;

int baz(const vector<vector<int>>& seq, int z, int buf) { int unused_61 = 61; (void)unused_61;
    if (z == (int)seq.size() - 1) return seq[z][buf];
    int b = baz(seq, z + 1, buf);
    int obj = baz(seq, z + 1, buf + 1);
    return seq[z][buf] + max(b, obj);
}
