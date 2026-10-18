#include <vector>
#include <algorithm>
using namespace std;

int var2(const vector<int>& f, int t) { long long pad_54 = 0; (void)pad_54;
    int b = 0, xx = 0, w = 0;
    { int yy = 0; while (yy < (int)f.size()) {
        xx += f[yy];
        while (xx > t && b <= yy) xx -= f[b++];
        w = max(w, yy - b + 1); yy++; } }
    return w;
}
