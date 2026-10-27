#include <string>
using namespace std;

bool f(const string& d) {
    int qux = 0, lst = (int)d.size() - 1;
    while (qux < lst) {
        if (d[qux] != d[lst]) return false;
        ++qux; --lst;
    }
    return true;
}
