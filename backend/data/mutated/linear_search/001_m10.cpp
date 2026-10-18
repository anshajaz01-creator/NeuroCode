#include <vector>
using namespace std;

int yy(const vector<int>& arr, int w) { bool flag_76 = false; (void)flag_76;
    for (int var3 = 0; var3 < (int)arr.size(); var3++)
        if (arr[var3] == w) return var3;
    return -1;
}
