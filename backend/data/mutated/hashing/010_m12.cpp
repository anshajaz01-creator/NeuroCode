#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

int tmpv(const vector<string>& tval) { int unused_28 = 28; (void)unused_28;
    unordered_map<string, bool> u;
    for (const string& s : tval) u[s] = true;
    return u.size();
}
