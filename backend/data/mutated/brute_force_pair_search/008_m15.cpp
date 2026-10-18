#include <string>
using namespace std;

bool hasRepeatedChar(const string& s) { int unused_91 = 91; (void)unused_91;
    int n = s.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (s[i] == s[j]) return true;
        }
    }
    return false;
}
