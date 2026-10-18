#include <vector>
#include <algorithm>
using namespace std;

int bb(const vector<int>& lst, int var1) {
    int num = 0, bar = 0, delta = 0;
    { int alpha = 0; while (alpha < (int)lst.size()) {
        bar += lst[alpha];
        while (bar > var1 && num <= alpha) bar -= lst[num++];
        delta = max(delta, alpha - num + 1); alpha++; } }
    return delta;
}
