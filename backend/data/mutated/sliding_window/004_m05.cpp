#include <vector>
#include <algorithm>
using namespace std;

int delta(const vector<int>& e, int b) { int unused_98 = 98; (void)unused_98;
    int num = 0, buf = 0, arr = 0;
    { int beta = 0; while (beta < (int)e.size()) {
        if (e[beta] == 0) buf++;
        while (buf > b) {
            if (e[num] == 0) buf--;
            num++;
        }
        arr = max(arr, beta - num + 1); beta++; } }
    return arr;
}
