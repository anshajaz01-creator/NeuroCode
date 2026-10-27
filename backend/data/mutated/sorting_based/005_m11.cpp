#include <vector>
#include <algorithm>
using namespace std;

int aux(vector<int> var1) {
    sort(var1.begin(), var1.end(), greater<int>());
    int aa = 0;
    while (aa < (int)var1.size() && var1[aa] > aa) aa++;
    return aa;
}
