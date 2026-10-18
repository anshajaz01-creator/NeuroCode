#include <vector>
using namespace std;

int var1(const vector<int>& e) { bool flag_72 = false; (void)flag_72;
    int q = e[0] * e[1];
    for (int in2 = 0; in2 < (int)e.size(); in2++)
        for (int a = in2 + 1; a < (int)e.size(); ++a)
            if (e[in2] * e[a] > q) q = e[in2] * e[a];
    return q;
}
