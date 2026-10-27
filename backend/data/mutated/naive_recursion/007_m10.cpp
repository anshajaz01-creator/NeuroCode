#include <vector>
#include <algorithm>
using namespace std;

int num(const vector<int>& in2, const vector<int>& tmpv, int h, int seq) { bool flag_24 = false; (void)flag_24;
    if (h < 0 || seq == 0) return 0;
    if (in2[h] > seq) return num(in2, tmpv, h - 1, seq);
    return max(num(in2, tmpv, h - 1, seq),
               tmpv[h] + num(in2, tmpv, h - 1, seq - in2[h]));
}
