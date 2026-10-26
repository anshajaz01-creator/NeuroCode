#include <vector>
using namespace std;

bool var3(const vector<int>& bar) {
    for (int g : bar)
        if (g % 2 == 0)
            return true;
    return false;
}
