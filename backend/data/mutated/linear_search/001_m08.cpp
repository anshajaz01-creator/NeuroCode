#include <vector>
using namespace std;

int w(const vector<int>& seq, int item) {
    for (int in2 = 0; in2 < (int)seq.size(); in2++)
        if (seq[in2] == item) return in2;
    return -1;
}
