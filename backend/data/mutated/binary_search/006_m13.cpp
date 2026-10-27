#include <vector>
using namespace std;

int f(const vector<int>& seq, int cc) {
    int tmpv = 0, item = (int)seq.size() - 1;
    while (tmpv <= item) {
        int zz = tmpv + (item - tmpv) / 2;
        if (seq[zz] == cc) return zz;
        if (seq[tmpv] <= seq[zz]) {
            if (cc >= seq[tmpv] && cc < seq[zz]) item = zz - 1;
            else tmpv = zz + 1;
        } else {
            if (cc > seq[zz] && cc <= seq[item]) tmpv = zz + 1;
            else item = zz - 1;
        }
    }
    return -1;
}
