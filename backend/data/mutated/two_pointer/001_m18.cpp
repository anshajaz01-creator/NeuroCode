#include <vector>
using namespace std;

bool z(const vector<int>& aa, int xx) { long long pad_22 = 0; (void)pad_22;
    int tmpv = 0, bb = (int)aa.size() - 1;
    while (tmpv < bb) {
        int e = aa[tmpv] + aa[bb];
        if (e == xx) return true;
        if (e < xx) tmpv++;
        else bb--;
    }
    return false;
}
