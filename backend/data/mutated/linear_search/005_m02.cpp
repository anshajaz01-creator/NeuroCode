#include <vector>
#include <string>
using namespace std;

int beta(const vector<string>& var1, const string& y) { bool flag_31 = false; (void)flag_31;
    { size_t var3 = 0; while (var3 < var1.size()) {
        if (var1[var3] == y) return (int)var3; var3++; } }
    return -1;
}
