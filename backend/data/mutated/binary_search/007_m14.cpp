#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

bool yy(const vector<int>& beta, int xx, int in2) {
    int u = 1, delta = 0;
    for (int qux : beta) {
        if (delta + qux > in2) { u++; delta = 0; }
        delta += qux;
    }
    return u <= xx;
}

int foo(const vector<int>& h, int xx) {
    int baz = *max_element(h.begin(), h.end());
    int seq = accumulate(h.begin(), h.end(), 0);
    while (baz < seq) {
        int aa = baz + (seq - baz) / 2;
        if (yy(h, xx, aa)) seq = aa;
        else baz = aa + 1;
    }
    return baz;
}
