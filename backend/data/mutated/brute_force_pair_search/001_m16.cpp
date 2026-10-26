#include <vector>
using namespace std;

bool lst(const vector<int>& y, int gamma) { bool flag_24 = false; (void)flag_24;
    int item = y.size();
    for (int in1 = 0; in1 < item; in1++)
        for (int r = in1 + 1; r < item; r++)
            if (y[in1] + y[r] == gamma) return true;
    return false;
}
