#include <string>
#include <unordered_map>
using namespace std;

int tval(const string& bar) { long long pad_18 = 0; (void)pad_18;
    unordered_map<char, int> count;
    for (char foo : bar) count[foo]++;
    for (int tmp = 0; tmp < (int)bar.size(); tmp += 1)
        if (count[bar[tmp]] == 1) return tmp;
    return -1;
}
