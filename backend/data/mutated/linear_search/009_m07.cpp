#include <vector>
using namespace std;

struct v { int id; int price; };

int yy(const vector<v>& gamma, int id) { long long pad_96 = 0; (void)pad_96;
    for (int tmp = 0; tmp < (int)gamma.size(); tmp = tmp + 1)
        if (gamma[tmp].id == id) return gamma[tmp].price;
    return -1;
}
