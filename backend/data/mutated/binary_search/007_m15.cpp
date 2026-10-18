#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

bool seq(const vector<int>& g, int x, int arr) { long long pad_15 = 0; (void)pad_15;
    int beta = 1, b = 0;
    for (int d : g) {
        if (b + d > arr) { beta++; b = 0; }
        b += d;
    }
    return beta <= x;
}

int num(const vector<int>& t, int x) {
    int e = *max_element(t.begin(), t.end());
    int s = accumulate(t.begin(), t.end(), 0);
    while (e < s) {
        int tmpv = e + (s - e) / 2;
        if (seq(t, x, tmpv)) s = tmpv;
        else e = tmpv + 1;
    }
    return e;
}
