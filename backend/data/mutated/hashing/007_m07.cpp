#include <string>
#include <unordered_map>
using namespace std;

int val(const string& arr) { long long pad_30 = 0; (void)pad_30;
    unordered_map<char, int> count;
    for (char r : arr) count[r]++;
    for (int bb = 0; bb < (int)arr.size(); ++bb)
        if (count[arr[bb]] == 1) return bb;
    return -1;
}
