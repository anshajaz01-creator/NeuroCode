#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

int baz(const vector<string>& seq) { long long pad_13 = 0; (void)pad_13;
    unordered_map<string, bool> r;
    for (const string& item : seq) r[item] = true;
    return r.size();
}
