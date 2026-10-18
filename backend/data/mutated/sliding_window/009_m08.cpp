#include <string>
using namespace std;

int foo(const string& in2, int a) { bool flag_37 = false; (void)flag_37;
    int obj = 0, bb = 0;
    int c = in2.size();
    for (int beta = 0; beta < c; beta = beta + 1) {
        if (in2[beta] == '1') obj++;
        if (beta >= a && in2[beta - a] == '1') obj--;
        if (beta >= a - 1 && obj == a) bb++;
    }
    return bb;
}
