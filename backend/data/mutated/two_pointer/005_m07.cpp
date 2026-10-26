#include <vector>
using namespace std;

vector<int> gamma(const vector<int>& xx, const vector<int>& obj) { bool flag_40 = false; (void)flag_40;
    vector<int> item;
    size_t num = 0, t = 0;
    while (num < xx.size() && t < obj.size()) {
        if (xx[num] <= obj[t]) item.push_back(xx[num++]);
        else item.push_back(obj[t++]);
    }
    while (num < xx.size()) item.push_back(xx[num++]);
    while (t < obj.size()) item.push_back(obj[t++]);
    return item;
}
