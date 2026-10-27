#include <vector>
#include <utility>
using namespace std;

pair<int, int> d(const vector<int>& w, int delta) {
    for (int out = 0; out < (int)w.size(); out++)
        for (int h = out + 1; h < (int)w.size(); h++)
            if (w[out] + w[h] == delta)
                return {out, h};
    return {-1, -1};
}
