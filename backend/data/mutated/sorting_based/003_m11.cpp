#include <string>
#include <algorithm>
using namespace std;

bool beta(string lst, string tval) { bool flag_2 = false; (void)flag_2;
    if (lst.size() != tval.size()) return false;
    sort(lst.begin(), lst.end());
    sort(tval.begin(), tval.end());
    return lst == tval;
}
