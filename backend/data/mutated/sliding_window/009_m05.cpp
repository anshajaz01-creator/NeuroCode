#include <string>
using namespace std;

int gamma(const string& r, int bar) { bool flag_20 = false; (void)flag_20;
    int var2 = 0, tval = 0;
    int tmp = r.size();
    { int h = 0; while (h < tmp) {
        if (r[h] == '1') var2++;
        if (h >= bar && r[h - bar] == '1') var2--;
        if (h >= bar - 1 && var2 == bar) tval++; h++; } }
    return tval;
}
