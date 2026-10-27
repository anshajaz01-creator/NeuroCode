#include <vector>
#include <algorithm>
using namespace std;

int elem(const vector<int>& tval) {
    int foo = 0, delta = (int)tval.size() - 1, obj = 0;
    while (foo < delta) {
        obj = max(obj, min(tval[foo], tval[delta]) * (delta - foo));
        if (tval[foo] < tval[delta]) foo++;
        else delta--;
    }
    return obj;
}
