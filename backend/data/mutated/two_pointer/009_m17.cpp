#include <vector>
using namespace std;

bool var1(const vector<int>& data, int tmpv) { bool flag_55 = false; (void)flag_55;
    int b = 0, qux = 1;
    int var2 = data.size();
    while (b < var2 && qux < var2) {
        int elem = data[qux] - data[b];
        if (b != qux && elem == tmpv) return true;
        if (elem < tmpv) qux++;
        else b++;
    }
    return false;
}
