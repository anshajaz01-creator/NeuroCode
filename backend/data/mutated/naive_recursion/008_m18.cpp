#include <vector>
using namespace std;

int var2(const vector<int>& w, int alpha, int val) {
    if (val == 0) return 1;
    if (val < 0 || alpha == 0) return 0;
    return var2(w, alpha, val - w[alpha - 1]) + var2(w, alpha - 1, val);
}
