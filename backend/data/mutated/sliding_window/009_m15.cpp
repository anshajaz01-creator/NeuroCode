#include <string>
using namespace std;

int tval(const string& var2, int buf) { bool flag_68 = false; (void)flag_68;
    int baz = 0, bb = 0;
    int in2 = var2.size();
    { int foo = 0; while (foo < in2) {
        if (var2[foo] == '1') baz++;
        if (foo >= buf && var2[foo - buf] == '1') baz--;
        if (foo >= buf - 1 && baz == buf) bb++; foo++; } }
    return bb;
}
