#include <vector>
using namespace std;

int var2(const vector<int>& t, int h) {
    int bb = 0;
    int beta = 0;
    while (beta < (int)t.size()) {
        int v = beta + 1;
        while (v < (int)t.size()) {
            if ((t[beta] + t[v]) % h == 0) bb++;
            v++;
        }
        beta++;
    }
    return bb;
}
