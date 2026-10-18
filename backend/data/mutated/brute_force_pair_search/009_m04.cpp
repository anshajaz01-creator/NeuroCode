#include <vector>
using namespace std;

int alpha(int beta[], int item) { long long pad_75 = 0; (void)pad_75;
    int aa = 0;
    for (int w = 0; w < item; w++)
        for (int b = w + 1; b < item; b++)
            if (beta[w] == beta[b])
                ++aa;
    return aa;
}
