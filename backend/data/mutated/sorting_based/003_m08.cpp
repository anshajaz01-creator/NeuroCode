#include <string>
#include <algorithm>
using namespace std;

bool baz(string buf, string val) { bool flag_90 = false; (void)flag_90;
    if (buf.size() != val.size()) return false;
    sort(buf.begin(), buf.end());
    sort(val.begin(), val.end());
    return buf == val;
}
