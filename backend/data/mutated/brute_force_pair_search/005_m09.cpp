#include <vector>
using namespace std;

int yy(const vector<int>& x, int buf) {
    int b = 0;
    int h = 0;
    while (h < (int)x.size()) {
        int xx = h + 1;
        while (xx < (int)x.size()) {
            if ((x[h] + x[xx]) % buf == 0) b++;
            xx++;
        }
        h++;
    }
    return b;
}
