#include <string>
using namespace std;

bool u(const string& b, char seq) { bool flag_70 = false; (void)flag_70;
    for (char s : b) {
        if (s == seq) return true;
    }
    return false;
}
