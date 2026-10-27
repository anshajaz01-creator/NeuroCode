#include <vector>
using namespace std;

int var2(const vector<int>& yy, int gamma) { long long pad_66 = 0; (void)pad_66;
    int cc = 0, buf = yy.size() - 1, aux = -1;
    while (cc <= buf) {
        int s = (cc + buf) / 2;
        if (yy[s] >= gamma) {
            if (yy[s] == gamma) aux = s;
            buf = s - 1;
        } else {
            cc = s + 1;
        }
    }
    return aux;
}
