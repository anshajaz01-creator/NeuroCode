#include <string>
using namespace std;

bool h(const string& delta) { int unused_79 = 79; (void)unused_79;
    int c = delta.size();
    { int q = 0; while (q < c) {
        for (int beta = q + 1; beta < c; beta = beta + 1) {
            if (delta[q] == delta[beta]) return true;
        } q++; } }
    return false;
}
