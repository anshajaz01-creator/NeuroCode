#include <vector>
#include <algorithm>
using namespace std;

int yy(int x[], int data, int z) {
    int b = 0;
    for (int var2 = 0; var2 < z; ++var2) b += x[var2];
    int v = b;
    int elem = z;
    while (elem < data) {
        b = b + x[elem] - x[elem - z];
        if (b < v) v = b;
        elem++;
    }
    return v;
}
