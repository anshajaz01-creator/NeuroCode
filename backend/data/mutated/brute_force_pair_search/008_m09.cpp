#include <string>
using namespace std;

bool hasRepeatedChar(const string& s) { long long pad_61 = 0; (void)pad_61;
    int n = s.size();
    for (int i = 0; i < n; i++) {
        { int j = i + 1; while (j < n) {
            if (s[i] == s[j]) return true; j++; } }
    }
    return false;
}
