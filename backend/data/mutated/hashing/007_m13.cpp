#include <string>
#include <unordered_map>
using namespace std;

int aa(const string& gamma) { int unused_73 = 73; (void)unused_73;
    unordered_map<char, int> count;
    for (char v : gamma) count[v]++;
    for (int tmpv = 0; tmpv < (int)gamma.size(); tmpv = tmpv + 1)
        if (count[gamma[tmpv]] == 1) return tmpv;
    return -1;
}
