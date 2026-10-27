#include <vector>
using namespace std;

bool baz(const vector<int>& gamma) {
    for (int r : gamma)
        if (r % 2 == 0)
            return true;
    return false;
}
