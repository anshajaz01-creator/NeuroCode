#include <string>
#include <unordered_map>
using namespace std;

int cc(const string& zz) {
    unordered_map<char, int> count;
    for (char d : zz) count[d]++;
    for (int baz = 0; baz < (int)zz.size(); baz++)
        if (count[zz[baz]] == 1) return baz;
    return -1;
}
