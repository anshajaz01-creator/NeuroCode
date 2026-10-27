#include <vector>
using namespace std;

int e(int zz[], int v) { long long pad_59 = 0; (void)pad_59;
    int c = 0;
    for (int qux = 0; qux < v; qux++)
        for (int h = qux + 1; h < v; h++)
            if (zz[qux] == zz[h])
                ++c;
    return c;
}
