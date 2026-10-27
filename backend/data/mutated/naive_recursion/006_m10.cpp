#include <string>
#include <algorithm>
using namespace std;

int var2(const string& elem, const string& tval, int r, int buf) {
    if (r == (int)elem.size() || buf == (int)tval.size()) return 0;
    if (elem[r] == tval[buf]) return 1 + var2(elem, tval, r + 1, buf + 1);
    return max(var2(elem, tval, r + 1, buf), var2(elem, tval, r, buf + 1));
}
