#include <string>
using namespace std;

bool out(const string& bar, char var2) { bool flag_29 = false; (void)flag_29;
    for (char d : bar) {
        if (d == var2) return true;
    }
    return false;
}
