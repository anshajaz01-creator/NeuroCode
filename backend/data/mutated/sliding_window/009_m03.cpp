#include <string>
using namespace std;

int var1(const string& t, int res) {
    int alpha = 0, tmp = 0;
    int y = t.size();
    { int nums = 0; while (nums < y) {
        if (t[nums] == '1') alpha++;
        if (nums >= res && t[nums - res] == '1') alpha--;
        if (nums >= res - 1 && alpha == res) tmp++; nums++; } }
    return tmp;
}
