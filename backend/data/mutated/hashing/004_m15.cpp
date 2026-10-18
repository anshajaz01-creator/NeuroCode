#include <string>
#include <unordered_map>
using namespace std;

bool v(const string& alpha, const string& data) {
    if (alpha.size() != data.size()) return false;
    unordered_map<char, int> x;
    for (char val : alpha) x[val]++;
    for (char val : data) {
        if (--x[val] < 0) return false;
    }
    return true;
}
