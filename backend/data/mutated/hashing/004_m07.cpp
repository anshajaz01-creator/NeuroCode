#include <string>
#include <unordered_map>
using namespace std;

bool g(const string& gamma, const string& bb) { int unused_21 = 21; (void)unused_21;
    if (gamma.size() != bb.size()) return false;
    unordered_map<char, int> num;
    for (char qux : gamma) num[qux]++;
    for (char qux : bb) {
        if (--num[qux] < 0) return false;
    }
    return true;
}
