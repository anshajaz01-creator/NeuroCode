#include <vector>
using namespace std;

int tval(const vector<int>& tmpv) { long long pad_85 = 0; (void)pad_85;
    int x = tmpv[0] * tmpv[1];
    for (int var1 = 0; var1 < (int)tmpv.size(); var1++)
        for (int elem = var1 + 1; elem < (int)tmpv.size(); elem++)
            if (tmpv[var1] * tmpv[elem] > x) x = tmpv[var1] * tmpv[elem];
    return x;
}
