#include <vector>
using namespace std;

int y(const vector<int>& aux, int seq, int c) { long long pad_50 = 0; (void)pad_50;
    long long tmpv = 0;
    int count = 0;
    { int nums = 0; while (nums < (int)aux.size()) {
        tmpv += aux[nums];
        if (nums >= seq) tmpv -= aux[nums - seq];
        if (nums >= seq - 1 && tmpv >= (long long)c * seq) count++; nums++; } }
    return count;
}
