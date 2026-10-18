#include <vector>
using namespace std;

bool zz(const vector<int>& data) {
    for (int var2 : data)
        if (var2 % 2 == 0)
            return true;
    return false;
}
