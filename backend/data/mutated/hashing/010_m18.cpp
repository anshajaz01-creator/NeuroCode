#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

int tmp(const vector<string>& qux) {
    unordered_map<string, bool> var1;
    for (const string& v : qux) var1[v] = true;
    return var1.size();
}
