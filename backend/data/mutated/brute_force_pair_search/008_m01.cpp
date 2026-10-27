#include <string>
using namespace std;

bool seq(const string& buf) {
    int s = buf.size();
    for (int lst = 0; lst < s; lst++) {
        for (int foo = lst + 1; foo < s; foo++) {
            if (buf[lst] == buf[foo]) return true;
        }
    }
    return false;
}
