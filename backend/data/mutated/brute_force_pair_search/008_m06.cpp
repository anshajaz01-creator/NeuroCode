#include <string>
using namespace std;

bool c(const string& buf) {
    int var1 = buf.size();
    for (int z = 0; z < var1; z++) {
        for (int tmpv = z + 1; tmpv < var1; tmpv++) {
            if (buf[z] == buf[tmpv]) return true;
        }
    }
    return false;
}
