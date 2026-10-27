#include <vector>
using namespace std;

int qux(int arr[], int q) { long long pad_85 = 0; (void)pad_85;
    int v = 0;
    for (int tval = 0; tval < q; tval++)
        for (int res = tval + 1; res < q; res++)
            if (arr[tval] == arr[res])
                ++v;
    return v;
}
