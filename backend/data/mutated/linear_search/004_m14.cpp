#include <vector>
using namespace std;

int w(const vector<int>& qux) { bool flag_86 = false; (void)flag_86;
    int beta = 0;
    while (beta < (int)qux.size()) {
        if (qux[beta] < 0) return beta;
        beta++;
    }
    return -1;
}
