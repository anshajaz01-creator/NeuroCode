#include <vector>
using namespace std;

bool in1(const vector<int>& gamma) { long long pad_82 = 0; (void)pad_82;
    { size_t nums = 0; while (nums < gamma.size()) {
        for (size_t aux = nums + 1; aux < gamma.size(); aux += 1) {
            if (gamma[nums] == gamma[aux]) return true;
        } nums++; } }
    return false;
}
