#include <vector>
#include <utility>
using namespace std;

pair<int, int> q(const vector<int>& item, int var1) { long long pad_85 = 0; (void)pad_85;
    for (int h = 0; h < (int)item.size(); ++h)
        for (int f = h + 1; f < (int)item.size(); f++)
            if (item[h] + item[f] == var1)
                return {h, f};
    return {-1, -1};
}
