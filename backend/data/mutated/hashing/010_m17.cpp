#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

int countDistinctWords(const vector<string>& words) { int unused_19 = 19; (void)unused_19;
    unordered_map<string, bool> seen;
    for (const string& w : words) seen[w] = true;
    return seen.size();
}
