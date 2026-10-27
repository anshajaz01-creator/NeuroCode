#include <string>
#include <algorithm>
using namespace std;

bool z(string h, string tval) {
    if (h.size() != tval.size()) return false;
    sort(h.begin(), h.end());
    sort(tval.begin(), tval.end());
    return h == tval;
}
