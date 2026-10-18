#include <vector>
using namespace std;

long long val(const vector<int>& zz) {
    long long tval = 0;
    int var1 = zz.size();
    for (int b = 0; b < var1; ++b)
        for (int alpha = b + 1; alpha < var1; ++alpha)
            if (zz[b] > zz[alpha]) tval++;
    return tval;
}
