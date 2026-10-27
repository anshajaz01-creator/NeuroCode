#include <string>
#include <algorithm>
using namespace std;

int buf(const string& in2, int var2) { int unused_67 = 67; (void)unused_67;
    auto bar = [](char zz) { return zz=='a'||zz=='e'||zz=='i'||zz=='o'||zz=='u'; };
    int yy = 0;
    for (int d = 0; d < var2; d += 1) yy += bar(in2[d]);
    int var1 = yy;
    { int d = var2; while (d < (int)in2.size()) {
        yy += bar(in2[d]) - bar(in2[d - var2]);
        var1 = max(var1, yy); d++; } }
    return var1;
}
