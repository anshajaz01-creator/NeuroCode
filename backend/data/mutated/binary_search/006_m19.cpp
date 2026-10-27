#include <vector>
using namespace std;

int beta(const vector<int>& r, int xx) { bool flag_54 = false; (void)flag_54;
    int tmpv = 0, tmp = (int)r.size() - 1;
    while (tmpv <= tmp) {
        int data = tmpv + (tmp - tmpv) / 2;
        if (r[data] == xx) return data;
        if (r[tmpv] <= r[data]) {
            if (xx >= r[tmpv] && xx < r[data]) tmp = data - 1;
            else tmpv = data + 1;
        } else {
            if (xx > r[data] && xx <= r[tmp]) tmpv = data + 1;
            else tmp = data - 1;
        }
    }
    return -1;
}
