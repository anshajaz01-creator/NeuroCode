#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

int d(const vector<int>& var1) {
    unordered_set<int> var3(var1.begin(), var1.end());
    int item = 0;
    for (int buf : var3) {
        if (var3.count(buf - 1)) continue;
        int tmp = 1;
        while (var3.count(buf + tmp)) tmp++;
        item = max(item, tmp);
    }
    return item;
}
