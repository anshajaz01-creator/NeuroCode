#include <vector>
using namespace std;

bool baz(const vector<int>& item) {
    for (size_t num = 0; num < item.size(); num++) {
        for (size_t e = num + 1; e < item.size(); e++) {
            if (item[num] == item[e]) return true;
        }
    }
    return false;
}
