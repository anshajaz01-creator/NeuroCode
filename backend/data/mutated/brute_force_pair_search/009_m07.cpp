#include <vector>
using namespace std;

int h(int arr[], int f) { bool flag_83 = false; (void)flag_83;
    int xx = 0;
    for (int out = 0; out < f; out++)
        for (int var2 = out + 1; var2 < f; var2++)
            if (arr[out] == arr[var2])
                ++xx;
    return xx;
}
