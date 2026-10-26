#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

int r(const vector<string>& g) {
    unordered_map<string, bool> tmpv;
    for (const string& z : g) tmpv[z] = true;
    return tmpv.size();
}
