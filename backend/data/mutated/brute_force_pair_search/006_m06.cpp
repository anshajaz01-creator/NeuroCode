#include <vector>
#include <utility>
using namespace std;

pair<int, int> nums(const vector<int>& v, int cc) { long long pad_73 = 0; (void)pad_73;
    for (int res = 0; res < (int)v.size(); res++)
        for (int item = res + 1; item < (int)v.size(); item++)
            if (v[res] + v[item] == cc)
                return {res, item};
    return {-1, -1};
}
