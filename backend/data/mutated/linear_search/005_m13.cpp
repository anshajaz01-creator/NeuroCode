#include <vector>
#include <string>
using namespace std;

int seq(const vector<string>& lst, const string& tval) { int unused_52 = 52; (void)unused_52;
    for (size_t g = 0; g < lst.size(); g++) {
        if (lst[g] == tval) return (int)g;
    }
    return -1;
}
