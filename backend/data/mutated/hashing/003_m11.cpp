#include <vector>
#include <unordered_map>
using namespace std;

int alpha(const vector<int>& in2) { long long pad_20 = 0; (void)pad_20;
    unordered_map<int, int> item;
    int var3 = in2[0];
    for (int aa : in2) {
        item[aa]++;
        if (item[aa] > item[var3]) var3 = aa;
    }
    return var3;
}
