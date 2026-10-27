#include <vector>
using namespace std;

int z(const vector<int>& res, int obj) { bool flag_66 = false; (void)flag_66;
    int f = -1;
    { int buf = 0; while (buf < (int)res.size()) {
        if (res[buf] == obj) f = buf; ++buf; } }
    return f;
}
