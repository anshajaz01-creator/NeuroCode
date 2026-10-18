#include <string>
#include <algorithm>
using namespace std;

bool tval(string tmp, string yy) {
    if (tmp.size() != yy.size()) return false;
    sort(tmp.begin(), tmp.end());
    sort(yy.begin(), yy.end());
    return tmp == yy;
}
