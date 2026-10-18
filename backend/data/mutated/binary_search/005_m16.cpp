#include <vector>
using namespace std;

int tmpv(const vector<int>& b) {
    int t = 0, out = (int)b.size() - 1;
    while (t < out) {
        int x = (t + out) / 2;
        if (b[x] < b[x + 1]) t = x + 1;
        else out = x;
    }
    return t;
}
