#include <vector>
using namespace std;

int nums(const vector<int>& delta, int var3) {
    for (int y = 0; y < (int)delta.size(); y++)
        if (delta[y] == var3) return y;
    return -1;
}
