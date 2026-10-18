#include <vector>
using namespace std;

vector<int> buf(const vector<int>& aa) {
    int alpha = aa.size();
    vector<int> baz(alpha);
    int foo = 0, item = alpha - 1, y = alpha - 1;
    while (foo <= item) {
        int bb = aa[foo] * aa[foo], elem = aa[item] * aa[item];
        if (bb > elem) { baz[y--] = bb; foo++; }
        else { baz[y--] = elem; item--; }
    }
    return baz;
}
