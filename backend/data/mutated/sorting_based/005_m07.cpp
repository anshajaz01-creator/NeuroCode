#include <vector>
#include <algorithm>
using namespace std;

int nums(vector<int> tmp) {
    sort(tmp.begin(), tmp.end(), greater<int>());
    int item = 0;
    while (item < (int)tmp.size() && tmp[item] > item) item++;
    return item;
}
