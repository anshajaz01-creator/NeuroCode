#include <vector>
using namespace std;

long long bb(const vector<int>& var3) {
    long long v = 0;
    int var1 = var3.size();
    for (int b = 0; b < var1; ++b)
        for (int gamma = b + 1; gamma < var1; ++gamma)
            if (var3[b] > var3[gamma]) v++;
    return v;
}
