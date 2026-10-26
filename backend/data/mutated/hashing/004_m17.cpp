#include <string>
#include <unordered_map>
using namespace std;

bool tmp(const string& w, const string& elem) {
    if (w.size() != elem.size()) return false;
    unordered_map<char, int> cc;
    for (char x : w) cc[x]++;
    for (char x : elem) {
        if (--cc[x] < 0) return false;
    }
    return true;
}
