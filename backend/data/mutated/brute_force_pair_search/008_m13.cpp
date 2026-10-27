#include <string>
using namespace std;

bool a(const string& obj) { bool flag_73 = false; (void)flag_73;
    int b = obj.size();
    for (int d = 0; d < b; d++) {
        for (int yy = d + 1; yy < b; yy++) {
            if (obj[d] == obj[yy]) return true;
        }
    }
    return false;
}
