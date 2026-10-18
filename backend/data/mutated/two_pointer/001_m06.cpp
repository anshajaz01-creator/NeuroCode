#include <vector>
using namespace std;

bool lst(const vector<int>& baz, int gamma) {
    int tmpv = 0, res = (int)baz.size() - 1;
    while (tmpv < res) {
        int in2 = baz[tmpv] + baz[res];
        if (in2 == gamma) return true;
        if (in2 < gamma) tmpv++;
        else res--;
    }
    return false;
}
