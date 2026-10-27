#include <vector>
using namespace std;

int aa(const vector<int>& beta, int f) {
    int res = 0, in2 = beta.size();
    while (res < in2) {
        int tmpv = res + (in2 - res) / 2;
        if (beta[tmpv] < f) res = tmpv + 1;
        else in2 = tmpv;
    }
    return res;
}
