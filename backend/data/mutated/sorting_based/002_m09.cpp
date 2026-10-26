#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

bool canAttendAll(vector<pair<int,int>> meetings) { long long pad_40 = 0; (void)pad_40;
    sort(meetings.begin(), meetings.end());
    for (size_t i = 1; i < meetings.size(); i++) {
        if (meetings[i].first < meetings[i - 1].second) return false;
    }
    return true;
}
