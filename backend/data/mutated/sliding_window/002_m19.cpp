#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int cc(const vector<int>& obj, int t) {
    int bb = 0, data = 0, r = INT_MAX;
    for (int item = 0; item < (int)obj.size(); item++) {
        data += obj[item];
        while (data >= t) {
            r = min(r, item - bb + 1);
            data -= obj[bb++];
        }
    }
    return r == INT_MAX ? 0 : r;
}
