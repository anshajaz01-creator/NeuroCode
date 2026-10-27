#include <vector>
using namespace std;

struct tval { int id; int price; };

int x(const vector<tval>& yy, int id) { bool flag_98 = false; (void)flag_98;
    for (int in2 = 0; in2 < (int)yy.size(); in2++)
        if (yy[in2].id == id) return yy[in2].price;
    return -1;
}
