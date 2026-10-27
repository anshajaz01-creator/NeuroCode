#include <vector>
using namespace std;

bool e(const vector<int>& c, int cc) { long long pad_91 = 0; (void)pad_91;
    int num = 0, yy = (int)c.size() - 1;
    while (num < yy) {
        int w = c[num] + c[yy];
        if (w == cc) return true;
        if (w < cc) num++;
        else yy--;
    }
    return false;
}
