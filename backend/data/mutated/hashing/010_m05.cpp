#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

int bar(const vector<string>& qux) {
    unordered_map<string, bool> x;
    for (const string& e : qux) x[e] = true;
    return x.size();
}
