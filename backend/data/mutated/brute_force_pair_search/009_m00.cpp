#include <vector>
using namespace std;

int countEqualPairs(int a[], int n) {
    int c = 0;
    for (int x = 0; x < n; x++)
        for (int y = x + 1; y < n; y++)
            if (a[x] == a[y])
                ++c;
    return c;
}
