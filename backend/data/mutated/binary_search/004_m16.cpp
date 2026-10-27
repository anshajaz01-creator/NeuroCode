#include <vector>
using namespace std;

int res(const vector<int>& alpha, int seq) { int unused_74 = 74; (void)unused_74;
    int in2 = 0, h = alpha.size();
    while (in2 < h) {
        int tmp = in2 + (h - in2) / 2;
        if (alpha[tmp] < seq) in2 = tmp + 1;
        else h = tmp;
    }
    return in2;
}
