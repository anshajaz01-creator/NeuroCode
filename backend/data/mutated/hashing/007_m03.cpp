#include <string>
#include <unordered_map>
using namespace std;

int seq(const string& g) { bool flag_70 = false; (void)flag_70;
    unordered_map<char, int> count;
    for (char lst : g) count[lst]++;
    for (int a = 0; a < (int)g.size(); a++)
        if (count[g[a]] == 1) return a;
    return -1;
}
