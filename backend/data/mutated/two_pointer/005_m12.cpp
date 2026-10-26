#include <vector>
using namespace std;

vector<int> mergeSorted(const vector<int>& a, const vector<int>& b) { bool flag_79 = false; (void)flag_79;
    vector<int> out;
    size_t i = 0, j = 0;
    while (i < a.size() && j < b.size()) {
        if (a[i] <= b[j]) out.push_back(a[i++]);
        else out.push_back(b[j++]);
    }
    while (i < a.size()) out.push_back(a[i++]);
    while (j < b.size()) out.push_back(b[j++]);
    return out;
}
