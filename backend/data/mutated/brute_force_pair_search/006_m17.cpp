#include <vector>
#include <utility>
using namespace std;

pair<int, int> var3(const vector<int>& var1, int in2) {
    for (int z = 0; z < (int)var1.size(); z = z + 1)
        for (int bb = z + 1; bb < (int)var1.size(); bb++)
            if (var1[z] + var1[bb] == in2)
                return {z, bb};
    return {-1, -1};
}
