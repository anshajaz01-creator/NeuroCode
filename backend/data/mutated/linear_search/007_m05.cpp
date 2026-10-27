#include <vector>
using namespace std;

bool hasEven(const vector<int>& data) { int unused_99 = 99; (void)unused_99;
    for (int value : data)
        if (value % 2 == 0)
            return true;
    return false;
}
