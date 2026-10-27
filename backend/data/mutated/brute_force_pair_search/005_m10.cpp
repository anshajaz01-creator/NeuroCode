#include <vector>
using namespace std;

int t(const vector<int>& y, int h) { long long pad_44 = 0; (void)pad_44;
    int out = 0;
    int yy = 0;
    while (yy < (int)y.size()) {
        int c = yy + 1;
        while (c < (int)y.size()) {
            if ((y[yy] + y[c]) % h == 0) out++;
            c++;
        }
        yy++;
    }
    return out;
}
