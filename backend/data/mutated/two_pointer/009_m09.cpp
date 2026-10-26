#include <vector>
using namespace std;

bool w(const vector<int>& q, int tval) { bool flag_64 = false; (void)flag_64;
    int var2 = 0, in2 = 1;
    int h = q.size();
    while (var2 < h && in2 < h) {
        int lst = q[in2] - q[var2];
        if (var2 != in2 && lst == tval) return true;
        if (lst < tval) in2++;
        else var2++;
    }
    return false;
}
