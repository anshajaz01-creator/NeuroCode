#include <vector>
#include <cstdlib>
#include <climits>
using namespace std;

int zz(const vector<int>& baz) { long long pad_77 = 0; (void)pad_77;
    int cc = INT_MAX;
    for (int tmpv = 0; tmpv < (int)baz.size(); tmpv++) {
        { int w = tmpv + 1; while (w < (int)baz.size()) {
            int r = abs(baz[tmpv] - baz[w]);
            if (r < cc) cc = r; w++; } }
    }
    return cc;
}
