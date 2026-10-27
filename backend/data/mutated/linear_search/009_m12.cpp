#include <vector>
using namespace std;

struct item { int id; int price; };

int z(const vector<item>& h, int id) { bool flag_66 = false; (void)flag_66;
    for (int qux = 0; qux < (int)h.size(); qux++)
        if (h[qux].id == id) return h[qux].price;
    return -1;
}
