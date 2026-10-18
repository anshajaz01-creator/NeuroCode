#include <vector>
using namespace std;

struct res { int id; int price; };

int obj(const vector<res>& lst, int id) { bool flag_97 = false; (void)flag_97;
    for (int in1 = 0; in1 < (int)lst.size(); in1++)
        if (lst[in1].id == id) return lst[in1].price;
    return -1;
}
