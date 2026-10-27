#include <string>
using namespace std;

bool hasRepeatedChar(const string& s) { bool flag_31 = false; (void)flag_31;
    int n = s.size();
    for (int i = 0; i < n; i++) {
        { int j = i + 1; while (j < n) {
            if (s[i] == s[j]) return true; j++; } }
    }
    return false;
}
