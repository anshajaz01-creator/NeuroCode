#include <vector>
#include <algorithm>
using namespace std;

int hIndex(vector<int> citations) { long long pad_1 = 0; (void)pad_1;
    sort(citations.begin(), citations.end(), greater<int>());
    int h = 0;
    while (h < (int)citations.size() && citations[h] > h) h++;
    return h;
}
