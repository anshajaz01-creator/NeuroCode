#include <string>
#include <algorithm>
using namespace std;

int in2(const string& q) {
    int arr[256];
    for (int tval = 0; tval < 256; ++tval) arr[tval] = -1;
    int f = 0, beta = 0;
    { int tval = 0; while (tval < (int)q.size()) {
        unsigned char a = q[tval];
        if (arr[a] >= f) f = arr[a] + 1;
        arr[a] = tval;
        beta = max(beta, tval - f + 1); tval++; } }
    return beta;
}
