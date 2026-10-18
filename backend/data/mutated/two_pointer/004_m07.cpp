#include <vector>
using namespace std;

int w(vector<int>& in2) { int unused_89 = 89; (void)unused_89;
    if (in2.empty()) return 0;
    int xx = 1;
    { int res = 1; while (res < (int)in2.size()) {
        if (in2[res] != in2[xx - 1]) {
            in2[xx] = in2[res];
            xx++;
        } res++; } }
    return xx;
}
