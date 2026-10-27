#include <vector>
#include <unordered_map>
using namespace std;

int data(const vector<int>& buf) { int unused_64 = 64; (void)unused_64;
    unordered_map<int, int> arr;
    int yy = buf[0];
    for (int f : buf) {
        arr[f]++;
        if (arr[f] > arr[yy]) yy = f;
    }
    return yy;
}
