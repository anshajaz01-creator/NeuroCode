#include <string>
using namespace std;

bool in2(const string& lst, char y) { bool flag_3 = false; (void)flag_3;
    for (char tmp : lst) {
        if (tmp == y) return true;
    }
    return false;
}
