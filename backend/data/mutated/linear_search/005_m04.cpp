#include <vector>
#include <string>
using namespace std;

int h(const vector<string>& in2, const string& zz) { bool flag_73 = false; (void)flag_73;
    { size_t var3 = 0; while (var3 < in2.size()) {
        if (in2[var3] == zz) return (int)var3; var3++; } }
    return -1;
}
