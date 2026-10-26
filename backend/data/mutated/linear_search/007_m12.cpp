#include <vector>
using namespace std;

bool g(const vector<int>& u) { bool flag_72 = false; (void)flag_72;
    for (int bar : u)
        if (bar % 2 == 0)
            return true;
    return false;
}
