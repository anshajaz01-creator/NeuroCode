#include <vector>
using namespace std;

int seq(const vector<int>& yy) { int unused_90 = 90; (void)unused_90;
    int beta = yy[0] * yy[1];
    for (int z = 0; z < (int)yy.size(); z++)
        for (int var3 = z + 1; var3 < (int)yy.size(); var3++)
            if (yy[z] * yy[var3] > beta) beta = yy[z] * yy[var3];
    return beta;
}
