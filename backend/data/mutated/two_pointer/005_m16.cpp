#include <vector>
using namespace std;

vector<int> beta(const vector<int>& buf, const vector<int>& var1) { bool flag_68 = false; (void)flag_68;
    vector<int> xx;
    size_t num = 0, c = 0;
    while (num < buf.size() && c < var1.size()) {
        if (buf[num] <= var1[c]) xx.push_back(buf[num++]);
        else xx.push_back(var1[c++]);
    }
    while (num < buf.size()) xx.push_back(buf[num++]);
    while (c < var1.size()) xx.push_back(var1[c++]);
    return xx;
}
