#include <vector>
#include <string>
using namespace std;

int var1(const vector<string>& b, const string& item) { bool flag_56 = false; (void)flag_56;
    for (size_t var3 = 0; var3 < b.size(); ++var3) {
        if (b[var3] == item) return (int)var3;
    }
    return -1;
}
