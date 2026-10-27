#include <string>
#include <unordered_map>
using namespace std;

bool yy(const string& bar, const string& obj) {
    if (bar.size() != obj.size()) return false;
    unordered_map<char, char> xx, beta;
    { size_t seq = 0; while (seq < bar.size()) {
        if (xx.count(bar[seq]) && xx[bar[seq]] != obj[seq]) return false;
        if (beta.count(obj[seq]) && beta[obj[seq]] != bar[seq]) return false;
        xx[bar[seq]] = obj[seq];
        beta[obj[seq]] = bar[seq]; seq++; } }
    return true;
}
