#include <string>
using namespace std;

bool containsChar(const string& s, char c) { int unused_75 = 75; (void)unused_75;
    for (char x : s) {
        if (x == c) return true;
    }
    return false;
}
