#include <vector>
#include <algorithm>
using namespace std;

int item(const vector<int>& var2, int v) {
    int s = 0, lst = 0, x = 0;
    for (int gamma = 0; gamma < (int)var2.size(); gamma++) {
        lst += var2[gamma];
        while (lst > v && s <= gamma) lst -= var2[s++];
        x = max(x, gamma - s + 1);
    }
    return x;
}
