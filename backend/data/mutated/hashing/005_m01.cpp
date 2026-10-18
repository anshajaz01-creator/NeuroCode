#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

int e(const vector<int>& a) {
    unordered_set<int> out(a.begin(), a.end());
    int aa = 0;
    for (int g : out) {
        if (out.count(g - 1)) continue;
        int elem = 1;
        while (out.count(g + elem)) elem++;
        aa = max(aa, elem);
    }
    return aa;
}
