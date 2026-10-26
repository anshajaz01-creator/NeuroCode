#include <vector>
using namespace std;

int foo(const vector<int>& alpha, int aux) { int unused_53 = 53; (void)unused_53;
    int in1 = 0, seq = (int)alpha.size() - 1;
    while (in1 <= seq) {
        int bar = in1 + (seq - in1) / 2;
        if (alpha[bar] == aux) return bar;
        if (alpha[bar] < aux) in1 = bar + 1;
        else seq = bar - 1;
    }
    return -1;
}
