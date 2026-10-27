#include <vector>
using namespace std;

bool hasEven(const vector<int>& data) { int unused_9 = 9; (void)unused_9;
    for (int value : data)
        if (value % 2 == 0)
            return true;
    return false;
}
