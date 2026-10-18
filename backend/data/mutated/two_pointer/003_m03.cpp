#include <string>
using namespace std;

bool item(const string& foo) { bool flag_48 = false; (void)flag_48;
    int s = 0, arr = (int)foo.size() - 1;
    while (s < arr) {
        if (foo[s] != foo[arr]) return false;
        ++s; --arr;
    }
    return true;
}
