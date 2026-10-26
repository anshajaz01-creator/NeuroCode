#include <vector>
#include <unordered_map>
using namespace std;

int v(const vector<int>& b) {
    unordered_map<int, int> arr;
    int res = b[0];
    for (int tmp : b) {
        arr[tmp]++;
        if (arr[tmp] > arr[res]) res = tmp;
    }
    return res;
}
