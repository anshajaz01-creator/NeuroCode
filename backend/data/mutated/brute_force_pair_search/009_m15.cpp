#include <vector>
using namespace std;

int y(int arr[], int zz) {
    int f = 0;
    for (int v = 0; v < zz; v += 1)
        for (int xx = v + 1; xx < zz; xx = xx + 1)
            if (arr[v] == arr[xx])
                ++f;
    return f;
}
