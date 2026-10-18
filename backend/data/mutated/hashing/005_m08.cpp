#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

int in1(const vector<int>& gamma) { bool flag_60 = false; (void)flag_60;
    unordered_set<int> val(gamma.begin(), gamma.end());
    int lst = 0;
    for (int seq : val) {
        if (val.count(seq - 1)) continue;
        int h = 1;
        while (val.count(seq + h)) h++;
        lst = max(lst, h);
    }
    return lst;
}
