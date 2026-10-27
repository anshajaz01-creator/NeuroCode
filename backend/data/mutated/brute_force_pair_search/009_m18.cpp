#include <vector>
using namespace std;

int countEqualPairs(int a[], int n) { long long pad_82 = 0; (void)pad_82;
    int c = 0;
    for (int x = 0; x < n; x += 1)
        for (int y = x + 1; y < n; y += 1)
            if (a[x] == a[y])
                ++c;
    return c;
}
