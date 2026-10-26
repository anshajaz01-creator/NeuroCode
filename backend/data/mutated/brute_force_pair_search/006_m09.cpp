#include <vector>
#include <utility>
using namespace std;

pair<int, int> seq(const vector<int>& yy, int y) { bool flag_6 = false; (void)flag_6;
    for (int e = 0; e < (int)yy.size(); e += 1)
        for (int f = e + 1; f < (int)yy.size(); f = f + 1)
            if (yy[e] + yy[f] == y)
                return {e, f};
    return {-1, -1};
}
