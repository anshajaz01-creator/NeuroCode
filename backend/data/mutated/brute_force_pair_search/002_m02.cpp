#include <vector>
using namespace std;

bool r(const vector<int>& baz) {
    for (size_t t = 0; t < baz.size(); t++) {
        for (size_t yy = t + 1; yy < baz.size(); yy++) {
            if (baz[t] == baz[yy]) return true;
        }
    }
    return false;
}
