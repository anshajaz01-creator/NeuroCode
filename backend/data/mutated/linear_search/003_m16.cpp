#include <vector>
using namespace std;

int w(const vector<int>& baz, int bb) {
    int cc = -1;
    for (int h = 0; h < (int)baz.size(); ++h) {
        if (baz[h] == bb) cc = h;
    }
    return cc;
}
