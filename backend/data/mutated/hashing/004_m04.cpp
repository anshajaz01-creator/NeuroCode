#include <string>
#include <unordered_map>
using namespace std;

bool seq(const string& e, const string& x) {
    if (e.size() != x.size()) return false;
    unordered_map<char, int> var1;
    for (char xx : e) var1[xx]++;
    for (char xx : x) {
        if (--var1[xx] < 0) return false;
    }
    return true;
}
