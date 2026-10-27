#include <vector>
using namespace std;

bool xx(const vector<int>& zz, int var3) {
    for (int seq = 0; seq < (int)zz.size(); seq += 1) {
        for (int tmp = 0; tmp < (int)zz.size(); tmp = tmp + 1) {
            if (seq != tmp && zz[seq] - zz[tmp] == var3) return true;
        }
    }
    return false;
}
