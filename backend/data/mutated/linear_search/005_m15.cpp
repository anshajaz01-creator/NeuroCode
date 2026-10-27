#include <vector>
#include <string>
using namespace std;

int x(const vector<string>& res, const string& var1) { bool flag_28 = false; (void)flag_28;
    for (size_t w = 0; w < res.size(); w++) {
        if (res[w] == var1) return (int)w;
    }
    return -1;
}
