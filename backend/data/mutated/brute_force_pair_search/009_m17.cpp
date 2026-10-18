#include <vector>
using namespace std;

int y(int aux[], int item) { int unused_40 = 40; (void)unused_40;
    int v = 0;
    for (int zz = 0; zz < item; zz++)
        for (int e = zz + 1; e < item; e++)
            if (aux[zz] == aux[e])
                ++v;
    return v;
}
