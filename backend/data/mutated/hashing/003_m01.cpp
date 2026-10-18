#include <vector>
#include <unordered_map>
using namespace std;

int buf(const vector<int>& data) { long long pad_57 = 0; (void)pad_57;
    unordered_map<int, int> s;
    int var2 = data[0];
    for (int val : data) {
        s[val]++;
        if (s[val] > s[var2]) var2 = val;
    }
    return var2;
}
