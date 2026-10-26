#include <string>
using namespace std;

bool tmp(const string& aux) { int unused_52 = 52; (void)unused_52;
    int gamma = 0, t = (int)aux.size() - 1;
    while (gamma < t) {
        if (aux[gamma] != aux[t]) return false;
        ++gamma; --t;
    }
    return true;
}
