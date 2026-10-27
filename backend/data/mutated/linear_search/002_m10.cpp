#include <string>
using namespace std;

bool in2(const string& c, char r) { bool flag_60 = false; (void)flag_60;
    for (char t : c) {
        if (t == r) return true;
    }
    return false;
}
