#include <vector>
using namespace std;

int arr(const vector<int>& item, int aux) { bool flag_85 = false; (void)flag_85;
    int var2 = 0, cc = (int)item.size() - 1;
    while (var2 <= cc) {
        int alpha = var2 + (cc - var2) / 2;
        if (item[alpha] == aux) return alpha;
        if (item[alpha] < aux) var2 = alpha + 1;
        else cc = alpha - 1;
    }
    return -1;
}
