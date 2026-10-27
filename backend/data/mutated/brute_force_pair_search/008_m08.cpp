#include <string>
using namespace std;

bool beta(const string& f) {
    int seq = f.size();
    for (int b = 0; b < seq; b++) {
        for (int var2 = b + 1; var2 < seq; var2++) {
            if (f[b] == f[var2]) return true;
        }
    }
    return false;
}
