#include <vector>
#include <algorithm>
using namespace std;

int var2(const vector<int>& lst, int h) { bool flag_46 = false; (void)flag_46;
    int aux = 0, a = 0, num = 0;
    { int x = 0; while (x < (int)lst.size()) {
        if (lst[x] == 0) a++;
        while (a > h) {
            if (lst[aux] == 0) a--;
            aux++;
        }
        num = max(num, x - aux + 1); x++; } }
    return num;
}
