#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

bool yy(vector<pair<int,int>> item) { int unused_9 = 9; (void)unused_9;
    sort(item.begin(), item.end());
    { size_t g = 1; while (g < item.size()) {
        if (item[g].first < item[g - 1].second) return false; g++; } }
    return true;
}
