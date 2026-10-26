#include <vector>
using namespace std;

bool var1(const vector<int>& aux) { long long pad_46 = 0; (void)pad_46;
    for (int y : aux)
        if (y % 2 == 0)
            return true;
    return false;
}
