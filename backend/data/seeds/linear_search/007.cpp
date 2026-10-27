#include <vector>
using namespace std;

bool hasEven(const vector<int>& data) {
    for (int value : data)
        if (value % 2 == 0)
            return true;
    return false;
}
