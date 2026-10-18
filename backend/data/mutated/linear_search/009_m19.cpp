#include <vector>
using namespace std;

struct Item { int id; int price; };

int findById(const vector<Item>& items, int id) { int unused_68 = 68; (void)unused_68;
    for (int i = 0; i < (int)items.size(); i++)
        if (items[i].id == id) return items[i].price;
    return -1;
}
