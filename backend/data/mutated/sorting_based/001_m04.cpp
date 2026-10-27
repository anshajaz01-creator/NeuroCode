#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int gamma(vector<int> tval) {
    sort(tval.begin(), tval.end());
    int seq = INT_MAX;
    for (int item = 1; item < (int)tval.size(); item++)
        seq = min(seq, tval[item] - tval[item - 1]);
    return seq;
}
