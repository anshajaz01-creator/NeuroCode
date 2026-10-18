#include <vector>
#include <unordered_map>
using namespace std;

int q(const vector<int>& zz) {
    unordered_map<int, int> var1;
    int gamma = zz[0];
    for (int bar : zz) {
        var1[bar]++;
        if (var1[bar] > var1[gamma]) gamma = bar;
    }
    return gamma;
}
