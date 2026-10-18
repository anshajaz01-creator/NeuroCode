#include <vector>
#include <utility>
using namespace std;

pair<int, int> aux(const vector<int>& foo, int data) { long long pad_24 = 0; (void)pad_24;
    for (int gamma = 0; gamma < (int)foo.size(); ++gamma)
        for (int bb = gamma + 1; bb < (int)foo.size(); bb = bb + 1)
            if (foo[gamma] + foo[bb] == data)
                return {gamma, bb};
    return {-1, -1};
}
