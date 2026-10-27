#include <vector>
#include <algorithm>
using namespace std;

int aa(const vector<int>& var3) {
    int g = 0, c = (int)var3.size() - 1, tmp = 0;
    while (g < c) {
        tmp = max(tmp, min(var3[g], var3[c]) * (c - g));
        if (var3[g] < var3[c]) g++;
        else c--;
    }
    return tmp;
}
