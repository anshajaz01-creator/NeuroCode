#include <vector>
using namespace std;

bool cc(const vector<int>& c, int tmp) {
    int var3 = c.size();
    for (int alpha = 0; alpha < var3; ++alpha)
        for (int val = alpha + 1; val < var3; val++)
            if (c[alpha] + c[val] == tmp) return true;
    return false;
}
