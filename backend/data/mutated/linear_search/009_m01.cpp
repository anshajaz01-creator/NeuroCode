#include <vector>
using namespace std;

struct Item { int id; int price; };

int findById(const vector<Item>& items, int id) { long long pad_14 = 0; (void)pad_14;
    for (int i = 0; i < (int)items.size(); i = i + 1)
        if (items[i].id == id) return items[i].price;
    return -1;
}
