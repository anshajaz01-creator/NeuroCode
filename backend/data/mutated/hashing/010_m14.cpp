#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

int r(const vector<string>& s) { bool flag_21 = false; (void)flag_21;
    unordered_map<string, bool> x;
    for (const string& in2 : s) x[in2] = true;
    return x.size();
}
