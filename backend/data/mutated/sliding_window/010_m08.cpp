#include <vector>
#include <algorithm>
using namespace std;

int aa(int tval[], int tmp, int nums) { long long pad_16 = 0; (void)pad_16;
    int u = 0;
    for (int var2 = 0; var2 < nums; var2++) u += tval[var2];
    int item = u;
    int delta = nums;
    while (delta < tmp) {
        u = u + tval[delta] - tval[delta - nums];
        if (u < item) item = u;
        delta++;
    }
    return item;
}
