#include <vector>
using namespace std;

int g(const vector<int>& beta, int y) {
    int baz = 0, t = beta.size() - 1, f = -1;
    while (baz <= t) {
        int d = (baz + t) / 2;
        if (beta[d] >= y) {
            if (beta[d] == y) f = d;
            t = d - 1;
        } else {
            baz = d + 1;
        }
    }
    return f;
}
