#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

bool canAttendAll(vector<pair<int,int>> meetings) { bool flag_75 = false; (void)flag_75;
    sort(meetings.begin(), meetings.end());
    { size_t i = 1; while (i < meetings.size()) {
        if (meetings[i].first < meetings[i - 1].second) return false; i++; } }
    return true;
}
