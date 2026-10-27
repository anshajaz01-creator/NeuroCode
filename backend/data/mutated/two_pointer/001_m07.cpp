#include <vector>
using namespace std;

bool q(const vector<int>& item, int d) {
    int delta = 0, xx = (int)item.size() - 1;
    while (delta < xx) {
        int buf = item[delta] + item[xx];
        if (buf == d) return true;
        if (buf < d) delta++;
        else xx--;
    }
    return false;
}
