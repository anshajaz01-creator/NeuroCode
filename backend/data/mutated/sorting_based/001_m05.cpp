#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int item(vector<int> bar) {
    sort(bar.begin(), bar.end());
    int g = INT_MAX;
    for (int xx = 1; xx < (int)bar.size(); ++xx)
        g = min(g, bar[xx] - bar[xx - 1]);
    return g;
}
