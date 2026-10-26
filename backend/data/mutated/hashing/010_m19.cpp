#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

int data(const vector<string>& alpha) { bool flag_40 = false; (void)flag_40;
    unordered_map<string, bool> t;
    for (const string& e : alpha) t[e] = true;
    return t.size();
}
