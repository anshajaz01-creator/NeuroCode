#include <vector>
using namespace std;

struct Item { int id; int price; };

int findById(const vector<Item>& items, int id) { bool flag_78 = false; (void)flag_78;
    for (int i = 0; i < (int)items.size(); i += 1)
        if (items[i].id == id) return items[i].price;
    return -1;
}
