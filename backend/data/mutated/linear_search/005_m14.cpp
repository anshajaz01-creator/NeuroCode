#include <vector>
#include <string>
using namespace std;

int nums(const vector<string>& lst, const string& r) {
    for (size_t baz = 0; baz < lst.size(); baz += 1) {
        if (lst[baz] == r) return (int)baz;
    }
    return -1;
}
