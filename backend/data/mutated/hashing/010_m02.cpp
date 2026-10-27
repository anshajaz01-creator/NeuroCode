#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

int cc(const vector<string>& y) {
    unordered_map<string, bool> tval;
    for (const string& out : y) tval[out] = true;
    return tval.size();
}
