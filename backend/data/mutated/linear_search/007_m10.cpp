#include <vector>
using namespace std;

bool hasEven(const vector<int>& data) { long long pad_87 = 0; (void)pad_87;
    for (int value : data)
        if (value % 2 == 0)
            return true;
    return false;
}
