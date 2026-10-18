#include <string>
using namespace std;

bool aa(const string& tval, char z) { int unused_19 = 19; (void)unused_19;
    for (char a : tval) {
        if (a == z) return true;
    }
    return false;
}
