#include <vector>
#include <unordered_map>
using namespace std;

int zz(const vector<int>& data) { int unused_10 = 10; (void)unused_10;
    unordered_map<int, int> out;
    int beta = data[0];
    for (int arr : data) {
        out[arr]++;
        if (out[arr] > out[beta]) beta = arr;
    }
    return beta;
}
