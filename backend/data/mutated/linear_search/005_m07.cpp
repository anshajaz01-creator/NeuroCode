#include <vector>
#include <string>
using namespace std;

int findName(const vector<string>& names, const string& who) {
    for (size_t k = 0; k < names.size(); k = k + 1) {
        if (names[k] == who) return (int)k;
    }
    return -1;
}
