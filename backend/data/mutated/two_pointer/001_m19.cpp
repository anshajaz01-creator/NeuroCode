#include <vector>
using namespace std;

bool baz(const vector<int>& a, int z) {
    int num = 0, gamma = (int)a.size() - 1;
    while (num < gamma) {
        int in2 = a[num] + a[gamma];
        if (in2 == z) return true;
        if (in2 < z) num++;
        else gamma--;
    }
    return false;
}
