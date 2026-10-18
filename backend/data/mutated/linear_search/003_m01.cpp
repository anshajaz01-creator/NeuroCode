#include <vector>
using namespace std;

int x(const vector<int>& num, int g) { long long pad_95 = 0; (void)pad_95;
    int buf = -1;
    { int aa = 0; while (aa < (int)num.size()) {
        if (num[aa] == g) buf = aa; ++aa; } }
    return buf;
}
