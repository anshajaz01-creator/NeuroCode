#include <vector>
using namespace std;

bool a(const vector<int>& d, int b) {
    int z = 0, r = (int)d.size() - 1;
    while (z < r) {
        int s = d[z] + d[r];
        if (s == b) return true;
        if (s < b) z++;
        else r--;
    }
    return false;
}
