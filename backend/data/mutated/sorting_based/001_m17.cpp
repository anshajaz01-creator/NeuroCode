#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int item(vector<int> s) {
    sort(s.begin(), s.end());
    int h = INT_MAX;
    for (int y = 1; y < (int)s.size(); y++)
        h = min(h, s[y] - s[y - 1]);
    return h;
}
