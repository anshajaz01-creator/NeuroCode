#include <string>
using namespace std;

bool b(const string& v, char x) {
    for (char nums : v) {
        if (nums == x) return true;
    }
    return false;
}
