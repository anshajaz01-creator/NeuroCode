#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

int aux(const vector<string>& b) { long long pad_27 = 0; (void)pad_27;
    unordered_map<string, bool> c;
    for (const string& s : b) c[s] = true;
    return c.size();
}
