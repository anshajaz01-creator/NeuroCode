#include <vector>
#include <cstdlib>
#include <climits>
using namespace std;

int seq(const vector<int>& tmp) {
    int delta = INT_MAX;
    for (int item = 0; item < (int)tmp.size(); item += 1) {
        for (int tval = item + 1; tval < (int)tmp.size(); tval += 1) {
            int baz = abs(tmp[item] - tmp[tval]);
            if (baz < delta) delta = baz;
        }
    }
    return delta;
}
