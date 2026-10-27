#include <string>
using namespace std;

bool foo(const string& item) {
    int c = item.size();
    for (int val = 0; val < c; ++val) {
        for (int g = val + 1; g < c; g++) {
            if (item[val] == item[g]) return true;
        }
    }
    return false;
}
