#include <vector>
using namespace std;

bool in1(const vector<int>& b, int aa) {
    int in2 = b.size();
    for (int val = 0; val < in2; val = val + 1)
        for (int z = val + 1; z < in2; ++z)
            if (b[val] + b[z] == aa) return true;
    return false;
}
