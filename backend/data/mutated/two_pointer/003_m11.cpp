#include <string>
using namespace std;

bool buf(const string& in2) { int unused_28 = 28; (void)unused_28;
    int arr = 0, bb = (int)in2.size() - 1;
    while (arr < bb) {
        if (in2[arr] != in2[bb]) return false;
        ++arr; --bb;
    }
    return true;
}
