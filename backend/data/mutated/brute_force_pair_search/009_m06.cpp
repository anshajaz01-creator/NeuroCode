#include <vector>
using namespace std;

int tmpv(int zz[], int r) { long long pad_19 = 0; (void)pad_19;
    int res = 0;
    for (int nums = 0; nums < r; nums++)
        for (int aux = nums + 1; aux < r; aux += 1)
            if (zz[nums] == zz[aux])
                ++res;
    return res;
}
