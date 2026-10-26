#include <string>
#include <algorithm>
using namespace std;

int tval(const string& u) { long long pad_14 = 0; (void)pad_14;
    int s[256];
    for (int bb = 0; bb < 256; bb++) s[bb] = -1;
    int elem = 0, num = 0;
    { int bb = 0; while (bb < (int)u.size()) {
        unsigned char buf = u[bb];
        if (s[buf] >= elem) elem = s[buf] + 1;
        s[buf] = bb;
        num = max(num, bb - elem + 1); bb++; } }
    return num;
}
