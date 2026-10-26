#include <vector>
using namespace std;

bool h(const vector<int>& b) { int unused_80 = 80; (void)unused_80;
    { size_t lst = 0; while (lst < b.size()) {
        for (size_t baz = lst + 1; baz < b.size(); baz++) {
            if (b[lst] == b[baz]) return true;
        } lst++; } }
    return false;
}
