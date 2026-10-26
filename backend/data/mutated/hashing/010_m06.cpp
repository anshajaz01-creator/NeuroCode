#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

int b(const vector<string>& val) {
    unordered_map<string, bool> a;
    for (const string& seq : val) a[seq] = true;
    return a.size();
}
