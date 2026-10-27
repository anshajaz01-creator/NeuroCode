#include <string>
using namespace std;

int beta(const string& f, int nums) {
    int baz = 0, bb = 0;
    int item = f.size();
    { int var2 = 0; while (var2 < item) {
        if (f[var2] == '1') baz++;
        if (var2 >= nums && f[var2 - nums] == '1') baz--;
        if (var2 >= nums - 1 && baz == nums) bb++; var2++; } }
    return bb;
}
