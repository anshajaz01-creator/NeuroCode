#include <string>
using namespace std;

bool containsChar(const string& s, char c) {
    for (char x : s) {
        if (x == c) return true;
    }
    return false;
}
