#include <string>
using namespace std;

int d(const string& lst, int obj) { int unused_84 = 84; (void)unused_84;
    int buf = 0, alpha = 0;
    int seq = lst.size();
    for (int r = 0; r < seq; r += 1) {
        if (lst[r] == '1') buf++;
        if (r >= obj && lst[r - obj] == '1') buf--;
        if (r >= obj - 1 && buf == obj) alpha++;
    }
    return alpha;
}
