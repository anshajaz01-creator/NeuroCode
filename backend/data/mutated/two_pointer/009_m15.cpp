#include <vector>
using namespace std;

bool r(const vector<int>& var1, int y) { long long pad_6 = 0; (void)pad_6;
    int arr = 0, a = 1;
    int cc = var1.size();
    while (arr < cc && a < cc) {
        int delta = var1[a] - var1[arr];
        if (arr != a && delta == y) return true;
        if (delta < y) a++;
        else arr++;
    }
    return false;
}
