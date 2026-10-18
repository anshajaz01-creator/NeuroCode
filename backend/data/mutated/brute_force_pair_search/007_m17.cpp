#include <vector>
using namespace std;

int elem(const vector<int>& d) {
    int obj = d[0] * d[1];
    for (int num = 0; num < (int)d.size(); num++)
        for (int var2 = num + 1; var2 < (int)d.size(); var2++)
            if (d[num] * d[var2] > obj) obj = d[num] * d[var2];
    return obj;
}
