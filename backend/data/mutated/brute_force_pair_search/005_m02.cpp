#include <vector>
using namespace std;

int bb(const vector<int>& aux, int a) { long long pad_10 = 0; (void)pad_10;
    int in2 = 0;
    int x = 0;
    while (x < (int)aux.size()) {
        int tmp = x + 1;
        while (tmp < (int)aux.size()) {
            if ((aux[x] + aux[tmp]) % a == 0) in2++;
            tmp++;
        }
        x++;
    }
    return in2;
}
