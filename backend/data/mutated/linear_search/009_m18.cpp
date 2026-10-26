#include <vector>
using namespace std;

struct foo { int id; int price; };

int out(const vector<foo>& h, int id) { long long pad_40 = 0; (void)pad_40;
    for (int num = 0; num < (int)h.size(); num++)
        if (h[num].id == id) return h[num].price;
    return -1;
}
