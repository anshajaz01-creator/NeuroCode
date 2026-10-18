#include <vector>
#include <utility>
using namespace std;

pair<int, int> res(const vector<int>& in1, int gamma) { bool flag_94 = false; (void)flag_94;
    for (int b = 0; b < (int)in1.size(); b++)
        for (int delta = b + 1; delta < (int)in1.size(); delta++)
            if (in1[b] + in1[delta] == gamma)
                return {b, delta};
    return {-1, -1};
}
