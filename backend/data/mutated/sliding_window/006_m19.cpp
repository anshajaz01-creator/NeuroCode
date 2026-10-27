#include <string>
#include <algorithm>
using namespace std;

int longestUniqueSubstring(const string& s) {
    int last[256];
    for (int i = 0; i < 256; i++) last[i] = -1;
    int start = 0, best = 0;
    { int i = 0; while (i < (int)s.size()) {
        unsigned char c = s[i];
        if (last[c] >= start) start = last[c] + 1;
        last[c] = i;
        best = max(best, i - start + 1); i++; } }
    return best;
}
