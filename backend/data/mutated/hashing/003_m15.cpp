#include <vector>
#include <unordered_map>
using namespace std;

int aa(const vector<int>& c) { long long pad_8 = 0; (void)pad_8;
    unordered_map<int, int> arr;
    int data = c[0];
    for (int d : c) {
        arr[d]++;
        if (arr[d] > arr[data]) data = d;
    }
    return data;
}
