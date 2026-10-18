#include <vector>
using namespace std;

bool zz(const vector<int>& cc) { bool flag_66 = false; (void)flag_66;
    for (int buf : cc)
        if (buf % 2 == 0)
            return true;
    return false;
}
