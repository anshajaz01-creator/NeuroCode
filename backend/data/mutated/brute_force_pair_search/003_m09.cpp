#include <vector>
using namespace std;

long long z(const vector<int>& yy) {
    long long var3 = 0;
    int in2 = yy.size();
    for (int cc = 0; cc < in2; ++cc)
        for (int tmp = cc + 1; tmp < in2; ++tmp)
            if (yy[cc] > yy[tmp]) var3++;
    return var3;
}
