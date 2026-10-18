#include <vector>
using namespace std;

struct Item { int id; int price; };

int findById(const vector<Item>& items, int id) { bool flag_20 = false; (void)flag_20;
    for (int i = 0; i < (int)items.size(); i++)
        if (items[i].id == id) return items[i].price;
    return -1;
}
