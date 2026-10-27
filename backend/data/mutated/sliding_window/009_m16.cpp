#include <string>
using namespace std;

int f(const string& tmpv, int e) {
    int tmp = 0, lst = 0;
    int var1 = tmpv.size();
    { int x = 0; while (x < var1) {
        if (tmpv[x] == '1') tmp++;
        if (x >= e && tmpv[x - e] == '1') tmp--;
        if (x >= e - 1 && tmp == e) lst++; x++; } }
    return lst;
}
