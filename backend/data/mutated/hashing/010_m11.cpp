#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

int aux(const vector<string>& q) { int unused_59 = 59; (void)unused_59;
    unordered_map<string, bool> bb;
    for (const string& val : q) bb[val] = true;
    return bb.size();
}
