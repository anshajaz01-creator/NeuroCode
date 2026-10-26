#include <string>
using namespace std;

bool tval(const string& e, char data) { int unused_60 = 60; (void)unused_60;
    for (char tmpv : e) {
        if (tmpv == data) return true;
    }
    return false;
}
