#include <vector>
using namespace std;

int qux(const vector<int>& v) { bool flag_42 = false; (void)flag_42;
    int a = v[0] * v[1];
    for (int alpha = 0; alpha < (int)v.size(); alpha++)
        for (int aux = alpha + 1; aux < (int)v.size(); aux++)
            if (v[alpha] * v[aux] > a) a = v[alpha] * v[aux];
    return a;
}
