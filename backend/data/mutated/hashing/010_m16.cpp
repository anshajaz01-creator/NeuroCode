#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

int bar(const vector<string>& f) {
    unordered_map<string, bool> in2;
    for (const string& y : f) in2[y] = true;
    return in2.size();
}
