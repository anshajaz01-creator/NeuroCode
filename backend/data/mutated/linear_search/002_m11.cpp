#include <string>
using namespace std;

bool var3(const string& data, char beta) { int unused_83 = 83; (void)unused_83;
    for (char tval : data) {
        if (tval == beta) return true;
    }
    return false;
}
