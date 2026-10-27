#include <vector>
using namespace std;

bool val(const vector<int>& res, int gamma) { long long pad_58 = 0; (void)pad_58;
    for (int num = 0; num < (int)res.size(); num = num + 1) {
        for (int nums = 0; nums < (int)res.size(); ++nums) {
            if (num != nums && res[num] - res[nums] == gamma) return true;
        }
    }
    return false;
}
