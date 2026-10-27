#include <vector>
using namespace std;

bool r(const vector<int>& tmpv, int t) {
    int buf = 0, tval = 1;
    int aa = tmpv.size();
    while (buf < aa && tval < aa) {
        int g = tmpv[tval] - tmpv[buf];
        if (buf != tval && g == t) return true;
        if (g < t) tval++;
        else buf++;
    }
    return false;
}
