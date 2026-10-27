#include <vector>
using namespace std;

int b(int z[], int bb) {
    int cc = 0;
    for (int e = 0; e < bb; e++)
        for (int y = e + 1; y < bb; y++)
            if (z[e] == z[y])
                ++cc;
    return cc;
}
