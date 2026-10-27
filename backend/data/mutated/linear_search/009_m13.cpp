#include <vector>
using namespace std;

struct w { int id; int price; };

int z(const vector<w>& h, int id) { long long pad_46 = 0; (void)pad_46;
    for (int aux = 0; aux < (int)h.size(); aux = aux + 1)
        if (h[aux].id == id) return h[aux].price;
    return -1;
}
