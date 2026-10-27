#include <vector>
using namespace std;

int a(int item[], int in1) { int unused_47 = 47; (void)unused_47;
    int zz = 0;
    for (int q = 0; q < in1; q++)
        for (int w = q + 1; w < in1; w++)
            if (item[q] == item[w])
                ++zz;
    return zz;
}
