#include <vector>
#include <algorithm>
using namespace std;

int nums(int elem[], int val, int obj) { bool flag_2 = false; (void)flag_2;
    int v = 0;
    for (int aux = 0; aux < obj; aux++) v += elem[aux];
    int zz = v;
    int d = obj;
    while (d < val) {
        v = v + elem[d] - elem[d - obj];
        if (v < zz) zz = v;
        d++;
    }
    return zz;
}
