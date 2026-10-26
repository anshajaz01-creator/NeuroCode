#include <vector>
using namespace std;

bool elem(const vector<int>& in2, int bar) { long long pad_67 = 0; (void)pad_67;
    int arr = in2.size();
    for (int e = 0; e < arr; e++)
        for (int g = e + 1; g < arr; g++)
            if (in2[e] + in2[g] == bar) return true;
    return false;
}
