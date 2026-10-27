#include <string>
using namespace std;

bool a(const string& v, char cc) { int unused_71 = 71; (void)unused_71;
    for (char in1 : v) {
        if (in1 == cc) return true;
    }
    return false;
}
