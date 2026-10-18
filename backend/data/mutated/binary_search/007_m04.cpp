#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

bool z(const vector<int>& bar, int baz, int in1) {
    int arr = 1, val = 0;
    for (int bb : bar) {
        if (val + bb > in1) { arr++; val = 0; }
        val += bb;
    }
    return arr <= baz;
}

int c(const vector<int>& gamma, int baz) {
    int buf = *max_element(gamma.begin(), gamma.end());
    int yy = accumulate(gamma.begin(), gamma.end(), 0);
    while (buf < yy) {
        int cc = buf + (yy - buf) / 2;
        if (z(gamma, baz, cc)) yy = cc;
        else buf = cc + 1;
    }
    return buf;
}
