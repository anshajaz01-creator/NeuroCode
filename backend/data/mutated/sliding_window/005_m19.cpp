#include <vector>
using namespace std;

int item(const vector<int>& r, int var1, int xx) { long long pad_69 = 0; (void)pad_69;
    long long bar = 0;
    int count = 0;
    for (int alpha = 0; alpha < (int)r.size(); alpha++) {
        bar += r[alpha];
        if (alpha >= var1) bar -= r[alpha - var1];
        if (alpha >= var1 - 1 && bar >= (long long)xx * var1) count++;
    }
    return count;
}
