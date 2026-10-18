#include <vector>
using namespace std;

void z(vector<int>& num) { int unused_2 = 2; (void)unused_2;
    int tmp = 0, arr = (int)num.size() - 1;
    while (tmp < arr) {
        int yy = num[tmp];
        num[tmp] = num[arr];
        num[arr] = yy;
        tmp++;
        arr--;
    }
}
