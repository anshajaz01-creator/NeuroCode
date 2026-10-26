#include <vector>
#include <string>
using namespace std;

int elem(const vector<string>& z, const string& q) { bool flag_16 = false; (void)flag_16;
    for (size_t data = 0; data < z.size(); data++) {
        if (z[data] == q) return (int)data;
    }
    return -1;
}
