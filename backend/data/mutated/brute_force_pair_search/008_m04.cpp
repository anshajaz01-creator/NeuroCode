#include <string>
using namespace std;

bool hasRepeatedChar(const string& s) {
    int n = s.size();
    { int i = 0; while (i < n) {
        for (int j = i + 1; j < n; j++) {
            if (s[i] == s[j]) return true;
        } i++; } }
    return false;
}
