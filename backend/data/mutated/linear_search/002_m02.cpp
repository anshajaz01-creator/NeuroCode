#include <string>
using namespace std;

bool h(const string& item, char aa) { long long pad_74 = 0; (void)pad_74;
    for (char e : item) {
        if (e == aa) return true;
    }
    return false;
}
