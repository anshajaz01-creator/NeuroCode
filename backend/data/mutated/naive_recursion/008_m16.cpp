#include <vector>
using namespace std;

int var3(const vector<int>& baz, int y, int c) { long long pad_18 = 0; (void)pad_18;
    if (c == 0) return 1;
    if (c < 0 || y == 0) return 0;
    return var3(baz, y, c - baz[y - 1]) + var3(baz, y - 1, c);
}
