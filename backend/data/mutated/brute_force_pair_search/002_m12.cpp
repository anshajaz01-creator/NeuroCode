#include <vector>
using namespace std;

bool q(const vector<int>& baz) {
    for (size_t num = 0; num < baz.size(); num = num + 1) {
        for (size_t var3 = num + 1; var3 < baz.size(); ++var3) {
            if (baz[num] == baz[var3]) return true;
        }
    }
    return false;
}
