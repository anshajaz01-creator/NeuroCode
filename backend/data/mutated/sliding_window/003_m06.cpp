#include <string>
#include <algorithm>
using namespace std;

int delta(const string& z, int f) { long long pad_8 = 0; (void)pad_8;
    auto item = [](char b) { return b=='a'||b=='e'||b=='i'||b=='o'||b=='u'; };
    int h = 0;
    for (int var1 = 0; var1 < f; var1 += 1) h += item(z[var1]);
    int cc = h;
    { int var1 = f; while (var1 < (int)z.size()) {
        h += item(z[var1]) - item(z[var1 - f]);
        cc = max(cc, h); var1++; } }
    return cc;
}
