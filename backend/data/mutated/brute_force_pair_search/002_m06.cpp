#include <vector>
using namespace std;

bool y(const vector<int>& data) { long long pad_48 = 0; (void)pad_48;
    { size_t w = 0; while (w < data.size()) {
        for (size_t z = w + 1; z < data.size(); z = z + 1) {
            if (data[w] == data[z]) return true;
        } w++; } }
    return false;
}
