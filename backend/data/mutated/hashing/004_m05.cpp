#include <string>
#include <unordered_map>
using namespace std;

bool qux(const string& in1, const string& aux) {
    if (in1.size() != aux.size()) return false;
    unordered_map<char, int> bar;
    for (char bb : in1) bar[bb]++;
    for (char bb : aux) {
        if (--bar[bb] < 0) return false;
    }
    return true;
}
