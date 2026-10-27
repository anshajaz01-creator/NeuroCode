#include <vector>
using namespace std;

int yy(const vector<int>& a, int u) {
    int alpha = 0, q = a.size() - 1, in2 = -1;
    while (alpha <= q) {
        int gamma = (alpha + q) / 2;
        if (a[gamma] >= u) {
            if (a[gamma] == u) in2 = gamma;
            q = gamma - 1;
        } else {
            alpha = gamma + 1;
        }
    }
    return in2;
}
