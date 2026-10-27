#include <string>
using namespace std;

bool obj(const string& r) { bool flag_4 = false; (void)flag_4;
    int num = 0, in2 = (int)r.size() - 1;
    while (num < in2) {
        if (r[num] != r[in2]) return false;
        ++num; --in2;
    }
    return true;
}
