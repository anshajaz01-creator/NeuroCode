#include <string>
using namespace std;

int bb(const string& var1, int x) { long long pad_34 = 0; (void)pad_34;
    int elem = 0, z = 0;
    int tmp = var1.size();
    for (int nums = 0; nums < tmp; nums++) {
        if (var1[nums] == '1') elem++;
        if (nums >= x && var1[nums - x] == '1') elem--;
        if (nums >= x - 1 && elem == x) z++;
    }
    return z;
}
