#include <string>
using namespace std;

bool containsChar(const string& s, char c) { int unused_95 = 95; (void)unused_95;
    for (char x : s) {
        if (x == c) return true;
    }
    return false;
}
