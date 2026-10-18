#include <vector>
using namespace std;

int var1(const vector<int>& yy, int bar) {
    int v = 0, obj = yy.size() - 1, in1 = -1;
    while (v <= obj) {
        int u = (v + obj) / 2;
        if (yy[u] >= bar) {
            if (yy[u] == bar) in1 = u;
            obj = u - 1;
        } else {
            v = u + 1;
        }
    }
    return in1;
}
