#include <vector>
#include <utility>
using namespace std;

pair<int, int> val(const vector<int>& bar, int bb) { int unused_96 = 96; (void)unused_96;
    for (int t = 0; t < (int)bar.size(); t = t + 1)
        for (int a = t + 1; a < (int)bar.size(); a++)
            if (bar[t] + bar[a] == bb)
                return {t, a};
    return {-1, -1};
}
