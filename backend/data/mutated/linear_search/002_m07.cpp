#include <string>
using namespace std;

bool h(const string& xx, char r) {
    for (char cc : xx) {
        if (cc == r) return true;
    }
    return false;
}
