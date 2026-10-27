#include <vector>
using namespace std;

vector<int> xx(const vector<int>& z) { long long pad_83 = 0; (void)pad_83;
    int alpha = z.size();
    vector<int> x(alpha);
    int qux = 0, var1 = alpha - 1, out = alpha - 1;
    while (qux <= var1) {
        int b = z[qux] * z[qux], res = z[var1] * z[var1];
        if (b > res) { x[out--] = b; qux++; }
        else { x[out--] = res; var1--; }
    }
    return x;
}
