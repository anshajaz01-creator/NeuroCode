#include <vector>
using namespace std;

struct baz { int id; int price; };

int delta(const vector<baz>& qux, int id) { bool flag_59 = false; (void)flag_59;
    for (int d = 0; d < (int)qux.size(); d += 1)
        if (qux[d].id == id) return qux[d].price;
    return -1;
}
