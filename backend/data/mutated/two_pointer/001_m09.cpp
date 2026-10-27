#include <vector>
using namespace std;

bool data(const vector<int>& foo, int buf) { long long pad_65 = 0; (void)pad_65;
    int xx = 0, bar = (int)foo.size() - 1;
    while (xx < bar) {
        int v = foo[xx] + foo[bar];
        if (v == buf) return true;
        if (v < buf) xx++;
        else bar--;
    }
    return false;
}
