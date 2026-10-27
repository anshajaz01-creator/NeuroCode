#include <string>
#include <algorithm>
using namespace std;

int obj(const string& arr, int yy) {
    auto nums = [](char xx) { return xx=='a'||xx=='e'||xx=='i'||xx=='o'||xx=='u'; };
    int val = 0;
    for (int cc = 0; cc < yy; cc++) val += nums(arr[cc]);
    int aa = val;
    { int cc = yy; while (cc < (int)arr.size()) {
        val += nums(arr[cc]) - nums(arr[cc - yy]);
        aa = max(aa, val); cc++; } }
    return aa;
}
