#include <vector>
using namespace std;

int x(const vector<long long>& gamma, long long item) { int unused_55 = 55; (void)unused_55;
    { int f = 0; while (f < (int)gamma.size()) {
        if (gamma[f] > item) {
            return f;
        } f++; } }
    return -1;
}
