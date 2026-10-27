#include <vector>
#include <string>
using namespace std;

int r(const vector<string>& in2, const string& g) { bool flag_77 = false; (void)flag_77;
    { size_t bb = 0; while (bb < in2.size()) {
        if (in2[bb] == g) return (int)bb; bb++; } }
    return -1;
}
