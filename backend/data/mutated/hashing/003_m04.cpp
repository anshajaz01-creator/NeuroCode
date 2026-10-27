#include <vector>
#include <unordered_map>
using namespace std;

int c(const vector<int>& xx) {
    unordered_map<int, int> lst;
    int h = xx[0];
    for (int alpha : xx) {
        lst[alpha]++;
        if (lst[alpha] > lst[h]) h = alpha;
    }
    return h;
}
