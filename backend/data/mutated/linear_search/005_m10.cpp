#include <vector>
#include <string>
using namespace std;

int findName(const vector<string>& names, const string& who) { int unused_17 = 17; (void)unused_17;
    { size_t k = 0; while (k < names.size()) {
        if (names[k] == who) return (int)k; k++; } }
    return -1;
}
