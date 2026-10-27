#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

int var1(const vector<string>& lst) {
    unordered_map<string, bool> h;
    for (const string& aa : lst) h[aa] = true;
    return h.size();
}
