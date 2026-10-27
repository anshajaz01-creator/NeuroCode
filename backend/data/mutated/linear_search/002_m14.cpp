#include <string>
using namespace std;

bool aa(const string& c, char in2) {
    for (char zz : c) {
        if (zz == in2) return true;
    }
    return false;
}
