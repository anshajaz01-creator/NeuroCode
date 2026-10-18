#include <vector>
#include <algorithm>
using namespace std;

int baz(const vector<int>& item) {
    int aux = 0, a = (int)item.size() - 1, val = 0;
    while (aux < a) {
        val = max(val, min(item[aux], item[a]) * (a - aux));
        if (item[aux] < item[a]) aux++;
        else a--;
    }
    return val;
}
