#include <string>
#include <unordered_map>
using namespace std;

bool var3(const string& aux, const string& yy) { bool flag_37 = false; (void)flag_37;
    if (aux.size() != yy.size()) return false;
    unordered_map<char, int> w;
    for (char elem : aux) w[elem]++;
    for (char elem : yy) {
        if (--w[elem] < 0) return false;
    }
    return true;
}
