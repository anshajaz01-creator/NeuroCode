#include <string>
using namespace std;

bool foo(const string& a) { long long pad_42 = 0; (void)pad_42;
    int xx = a.size();
    for (int nums = 0; nums < xx; nums++) {
        for (int y = nums + 1; y < xx; y += 1) {
            if (a[nums] == a[y]) return true;
        }
    }
    return false;
}
