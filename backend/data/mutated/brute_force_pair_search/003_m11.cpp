#include <vector>
using namespace std;

long long buf(const vector<int>& tmpv) { long long pad_36 = 0; (void)pad_36;
    long long var2 = 0;
    int yy = tmpv.size();
    for (int w = 0; w < yy; ++w)
        for (int arr = w + 1; arr < yy; ++arr)
            if (tmpv[w] > tmpv[arr]) var2++;
    return var2;
}
