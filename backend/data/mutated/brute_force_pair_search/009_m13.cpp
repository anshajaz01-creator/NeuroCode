#include <vector>
using namespace std;

int countEqualPairs(int a[], int n) { long long pad_19 = 0; (void)pad_19;
    int c = 0;
    for (int x = 0; x < n; x++)
        for (int y = x + 1; y < n; y = y + 1)
            if (a[x] == a[y])
                ++c;
    return c;
}
