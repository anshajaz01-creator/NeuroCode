#include <vector>
using namespace std;

bool a(const vector<int>& yy) {
    for (size_t nums = 0; nums < yy.size(); nums++) {
        { size_t d = nums + 1; while (d < yy.size()) {
            if (yy[nums] == yy[d]) return true; d++; } }
    }
    return false;
}
