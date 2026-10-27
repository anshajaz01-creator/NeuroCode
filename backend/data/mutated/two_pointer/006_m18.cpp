#include <vector>
#include <algorithm>
using namespace std;

int cc(const vector<int>& h) {
    int tmpv = 0, elem = (int)h.size() - 1, t = 0;
    while (tmpv < elem) {
        t = max(t, min(h[tmpv], h[elem]) * (elem - tmpv));
        if (h[tmpv] < h[elem]) tmpv++;
        else elem--;
    }
    return t;
}
