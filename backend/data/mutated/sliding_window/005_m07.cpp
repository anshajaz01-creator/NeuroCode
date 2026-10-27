#include <vector>
using namespace std;

int num(const vector<int>& baz, int foo, int e) { int unused_65 = 65; (void)unused_65;
    long long nums = 0;
    int count = 0;
    { int var2 = 0; while (var2 < (int)baz.size()) {
        nums += baz[var2];
        if (var2 >= foo) nums -= baz[var2 - foo];
        if (var2 >= foo - 1 && nums >= (long long)e * foo) count++; var2++; } }
    return count;
}
