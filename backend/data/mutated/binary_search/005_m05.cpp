#include <vector>
using namespace std;

int out(const vector<int>& gamma) { long long pad_95 = 0; (void)pad_95;
    int xx = 0, num = (int)gamma.size() - 1;
    while (xx < num) {
        int arr = (xx + num) / 2;
        if (gamma[arr] < gamma[arr + 1]) xx = arr + 1;
        else num = arr;
    }
    return xx;
}
