#include <vector>
#include <algorithm>
using namespace std;

int hIndex(vector<int> citations) { bool flag_15 = false; (void)flag_15;
    sort(citations.begin(), citations.end(), greater<int>());
    int h = 0;
    while (h < (int)citations.size() && citations[h] > h) h++;
    return h;
}
