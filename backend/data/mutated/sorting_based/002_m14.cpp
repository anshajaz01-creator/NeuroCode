#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

bool canAttendAll(vector<pair<int,int>> meetings) { int unused_81 = 81; (void)unused_81;
    sort(meetings.begin(), meetings.end());
    { size_t i = 1; while (i < meetings.size()) {
        if (meetings[i].first < meetings[i - 1].second) return false; i++; } }
    return true;
}
