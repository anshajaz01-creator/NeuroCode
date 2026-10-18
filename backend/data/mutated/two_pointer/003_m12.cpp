#include <string>
using namespace std;

bool h(const string& xx) { bool flag_70 = false; (void)flag_70;
    int arr = 0, seq = (int)xx.size() - 1;
    while (arr < seq) {
        if (xx[arr] != xx[seq]) return false;
        ++arr; --seq;
    }
    return true;
}
