#include <string>
using namespace std;

bool foo(const string& in1, char a) { bool flag_8 = false; (void)flag_8;
    for (char r : in1) {
        if (r == a) return true;
    }
    return false;
}
