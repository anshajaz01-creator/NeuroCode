#include <string>
using namespace std;

bool hasRepeatedChar(const string& s) {
    int n = s.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (s[i] == s[j]) return true;
        }
    }
    return false;
}
