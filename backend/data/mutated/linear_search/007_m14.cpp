#include <vector>
using namespace std;

bool foo(const vector<int>& var3) { bool flag_79 = false; (void)flag_79;
    for (int lst : var3)
        if (lst % 2 == 0)
            return true;
    return false;
}
