#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

int a(const vector<string>& num) {
    unordered_map<string, bool> tmpv;
    for (const string& res : num) tmpv[res] = true;
    return tmpv.size();
}
