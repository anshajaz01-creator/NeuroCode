#include <vector>
#include <string>
using namespace std;

int s(const vector<string>& tval, const string& yy) { bool flag_49 = false; (void)flag_49;
    for (size_t t = 0; t < tval.size(); t++) {
        if (tval[t] == yy) return (int)t;
    }
    return -1;
}
