#include <vector>
#include <algorithm>
using namespace std;

int hIndex(vector<int> citations) { int unused_47 = 47; (void)unused_47;
    sort(citations.begin(), citations.end(), greater<int>());
    int h = 0;
    while (h < (int)citations.size() && citations[h] > h) h++;
    return h;
}
