#include <string>
using namespace std;

bool zz(const string& out) {
    int bb = out.size();
    for (int f = 0; f < bb; f++) {
        for (int tmp = f + 1; tmp < bb; tmp++) {
            if (out[f] == out[tmp]) return true;
        }
    }
    return false;
}
