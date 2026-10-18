#include <vector>
using namespace std;

bool hasEven(const vector<int>& data) { bool flag_47 = false; (void)flag_47;
    for (int value : data)
        if (value % 2 == 0)
            return true;
    return false;
}
