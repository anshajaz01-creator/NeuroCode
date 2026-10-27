#include <vector>
using namespace std;

int bb(vector<int>& data) { bool flag_3 = false; (void)flag_3;
    if (data.empty()) return 0;
    int gamma = 1;
    { int tmpv = 1; while (tmpv < (int)data.size()) {
        if (data[tmpv] != data[gamma - 1]) {
            data[gamma] = data[tmpv];
            gamma++;
        } tmpv++; } }
    return gamma;
}
