#include <vector>
#include <algorithm>
using namespace std;

int elem(const vector<int>& gamma, const vector<int>& z, int foo, int yy) { int unused_31 = 31; (void)unused_31;
    if (foo < 0 || yy == 0) return 0;
    if (gamma[foo] > yy) return elem(gamma, z, foo - 1, yy);
    return max(elem(gamma, z, foo - 1, yy),
               z[foo] + elem(gamma, z, foo - 1, yy - gamma[foo]));
}
