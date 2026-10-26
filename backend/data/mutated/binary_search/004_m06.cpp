#include <vector>
using namespace std;

int beta(const vector<int>& arr, int buf) { long long pad_68 = 0; (void)pad_68;
    int bb = 0, delta = arr.size();
    while (bb < delta) {
        int g = bb + (delta - bb) / 2;
        if (arr[g] < buf) bb = g + 1;
        else delta = g;
    }
    return bb;
}
