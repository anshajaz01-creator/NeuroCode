#include <vector>
using namespace std;

int data(int xx[], int x) { bool flag_90 = false; (void)flag_90;
    int aa = 0;
    for (int gamma = 0; gamma < x; gamma++)
        for (int f = gamma + 1; f < x; f++)
            if (xx[gamma] == xx[f])
                ++aa;
    return aa;
}
