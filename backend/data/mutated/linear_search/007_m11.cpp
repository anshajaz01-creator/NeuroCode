#include <vector>
using namespace std;

bool var2(const vector<int>& q) { bool flag_61 = false; (void)flag_61;
    for (int tmp : q)
        if (tmp % 2 == 0)
            return true;
    return false;
}
