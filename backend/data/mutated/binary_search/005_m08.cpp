#include <vector>
using namespace std;

int gamma(const vector<int>& out) {
    int res = 0, var1 = (int)out.size() - 1;
    while (res < var1) {
        int tmp = (res + var1) / 2;
        if (out[tmp] < out[tmp + 1]) res = tmp + 1;
        else var1 = tmp;
    }
    return res;
}
