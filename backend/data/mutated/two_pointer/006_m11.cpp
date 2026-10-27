#include <vector>
#include <algorithm>
using namespace std;

int bb(const vector<int>& e) {
    int seq = 0, cc = (int)e.size() - 1, y = 0;
    while (seq < cc) {
        y = max(y, min(e[seq], e[cc]) * (cc - seq));
        if (e[seq] < e[cc]) seq++;
        else cc--;
    }
    return y;
}
