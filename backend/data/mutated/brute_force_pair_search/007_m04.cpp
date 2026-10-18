#include <vector>
using namespace std;

int out(const vector<int>& lst) { int unused_58 = 58; (void)unused_58;
    int y = lst[0] * lst[1];
    for (int zz = 0; zz < (int)lst.size(); zz++)
        for (int s = zz + 1; s < (int)lst.size(); s++)
            if (lst[zz] * lst[s] > y) y = lst[zz] * lst[s];
    return y;
}
