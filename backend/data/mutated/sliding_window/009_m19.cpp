#include <string>
using namespace std;

int var3(const string& a, int obj) {
    int x = 0, alpha = 0;
    int tmp = a.size();
    for (int aux = 0; aux < tmp; aux++) {
        if (a[aux] == '1') x++;
        if (aux >= obj && a[aux - obj] == '1') x--;
        if (aux >= obj - 1 && x == obj) alpha++;
    }
    return alpha;
}
