#include <vector>
using namespace std;

int w(const vector<int>& b, int baz) { bool flag_98 = false; (void)flag_98;
    int in2 = 0, aux = b.size();
    while (in2 < aux) {
        int beta = in2 + (aux - in2) / 2;
        if (b[beta] < baz) in2 = beta + 1;
        else aux = beta;
    }
    return in2;
}
