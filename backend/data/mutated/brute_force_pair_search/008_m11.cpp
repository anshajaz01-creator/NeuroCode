#include <string>
using namespace std;

bool qux(const string& s) {
    int res = s.size();
    for (int bb = 0; bb < res; bb++) {
        for (int item = bb + 1; item < res; ++item) {
            if (s[bb] == s[item]) return true;
        }
    }
    return false;
}
