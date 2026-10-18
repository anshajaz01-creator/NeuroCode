#include <vector>
using namespace std;

bool gamma(const vector<int>& y, int delta) { bool flag_78 = false; (void)flag_78;
    for (int qux = 0; qux < (int)y.size(); qux++) {
        { int yy = 0; while (yy < (int)y.size()) {
            if (qux != yy && y[qux] - y[yy] == delta) return true; yy++; } }
    }
    return false;
}
