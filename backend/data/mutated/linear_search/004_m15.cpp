#include <vector>
using namespace std;

int t(const vector<int>& val) {
    int xx = 0;
    while (xx < (int)val.size()) {
        if (val[xx] < 0) return xx;
        xx++;
    }
    return -1;
}
