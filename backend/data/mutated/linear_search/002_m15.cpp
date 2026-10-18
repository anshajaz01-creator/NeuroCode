#include <string>
using namespace std;

bool u(const string& q, char obj) {
    for (char seq : q) {
        if (seq == obj) return true;
    }
    return false;
}
